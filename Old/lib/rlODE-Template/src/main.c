/*
 * Copyright (c) 2021 Chris Camacho (codifies -  http://bedroomcoders.co.uk/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "raylib.h"
#include "raymath.h"



#include <ode/ode.h>
#include "raylibODE.h"

#include "assert.h"

/*
 * get ODE from https://bitbucket.org/odedevs/ode/downloads/
 *
 * extract ode 0.16.2 into the main directory of this project
 * 
 * cd into it
 * 
 * I'd suggest building it with this configuration
 * ./configure --enable-ou --enable-libccd --with-box-cylinder=libccd --with-drawstuff=none --disable-demos --with-libccd=internal
 *
 * and run make, you should then be set to compile this project
 */


// globals in use by near callback
dWorldID world;
dJointGroupID contactgroup;


int numObj = 500; // number of bodies

inline float rndf(float min, float max);

float rndf(float min, float max) 
{
    return ((float)rand() / (float)(RAND_MAX)) * (max - min) + min;
}

// when objects potentially collide this callback is called
// you can rule out certain collisions or use different surface parameters
// depending what object types collide.... lots of flexibility and power here!
#define MAX_CONTACTS 8

static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
    (void)data;
    int i;

    // exit without doing anything if the two bodies are connected by a joint
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    //if (b1==b2) return;
    if (b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact))
        return;
        
    if (!checkColliding(o1)) return;
    if (!checkColliding(o2)) return;

    // getting these just so can sometimes be a little bit of a black art!
    dContact contact[MAX_CONTACTS]; // up to MAX_CONTACTS contacts per body-body
    for (i = 0; i < MAX_CONTACTS; i++) {
        contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
                                    dContactSoftERP | dContactSoftCFM | dContactApprox1;
        contact[i].surface.mu = 1000;
        contact[i].surface.slip1 = 0.0001;
        contact[i].surface.slip2 = 0.001;
        contact[i].surface.soft_erp = 0.5;
        contact[i].surface.soft_cfm = 0.003;

        contact[i].surface.bounce = 0.1;
        contact[i].surface.bounce_vel = 0.1;

    }
    int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom,
                        sizeof(dContact));
    if (numc) {
        dMatrix3 RI;
        dRSetIdentity(RI);
        for (i = 0; i < numc; i++) {
            dJointID c =
                dJointCreateContact(world, contactgroup, contact + i);
            dJointAttach(c, b1, b2);
        }
    }

}

// a space can have multiple "worlds" for example you might have different
// sub levels that never interact, or the inside and outside of a building
dSpaceID space;

void makeStatic(Vector3 pos, Vector3 size) 
{
    dGeomID geom;
    geom = dCreateBox(space, size.x, size.y, size.z);
    dGeomSetPosition(geom, pos.x, pos.y, pos.z);     
}

int main(void)
{
    assert(sizeof(dReal) == sizeof(float));
    srand ( time(NULL) );

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920/2;
    const int screenHeight = 1080/2;

    // create an array of bodies
    dBodyID obj[numObj];

    SetWindowState(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib ODE");

    // Define the camera to look into our 3d world
    Camera camera = {(Vector3){ 15.0f, 10.0f, 15.0f }, (Vector3){ 0.0f, 0.5f, 0.0f },
                        (Vector3){ 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE};

    dInitODE2(0);   // initialise and create the physics
    dAllocateODEDataForThread(dAllocateMaskAll);
    
    world = dWorldCreate();
    printf("phys iterations per step %i\n",dWorldGetQuickStepNumIterations(world));
    space = dHashSpaceCreate(NULL);
    contactgroup = dJointGroupCreate(0);
    dWorldSetGravity(world, 0, -9.8, 0);    // gravity
    
    dWorldSetAutoDisableFlag (world, 1);
    dWorldSetAutoDisableLinearThreshold (world, 0.05);
    dWorldSetAutoDisableAngularThreshold (world, 0.05);
    dWorldSetLinearDamping(world, 0.005);
    dWorldSetAngularDamping(world, 0.005);

    dWorldSetAutoDisableSteps (world, 4);

    setupModels();
    
    // create the physics bodies
    for (int i = 0; i < numObj; i++) {
        obj[i] = dBodyCreate(world);
        dGeomID geom;
        dMatrix3 R;
        dMass m;
        float typ = rndf(0,1);
        if (typ < .25) {                //  box
            Vector3 s = (Vector3){rndf(0.25, .5), rndf(0.25, .5), rndf(0.25, .5)};
            geom = dCreateBox(space, s.x, s.y, s.z);
            dMassSetBox (&m, 10, s.x, s.y, s.z);
        } else if (typ < .5) {          //  sphere
            float r = rndf(0.125, .25);
            geom = dCreateSphere(space, r);
            dMassSetSphere(&m, 10, r);
        } else if (typ < .75) {         //  cylinder
            float l = rndf(0.125, .5);
            float r = rndf(0.125, .5);
            geom = dCreateCylinder(space, r, l);
            dMassSetCylinder(&m, 10, 3, r, l);
        } else {                        //  composite of cylinder with 2 spheres
            float l = rndf(.5,1.0);
            
            geom = dCreateCylinder(space, 0.125, l);
            dGeomID geom2 = dCreateSphere(space, l/2);
            dGeomID geom3 = dCreateSphere(space, l/2);

            
            dMass m2,m3;
            dMassSetSphere(&m2, 10, l/2);
            dMassTranslate(&m2,0, 0, l - 0.25);
            dMassSetSphere(&m3, 10, l/2);
            dMassTranslate(&m3,0, 0, -l + 0.25);
            dMassSetCylinder(&m, 10, 3, .25, l);
            dMassAdd(&m2, &m3);
            dMassAdd(&m, &m2);
            
            dGeomSetBody(geom2, obj[i]);
            dGeomSetBody(geom3, obj[i]);
            dGeomSetOffsetPosition(geom2, 0, 0, l - 0.25);
            dGeomSetOffsetPosition(geom3, 0, 0, -l + 0.25);

        }

        // give the body a random position and rotation
        dBodySetPosition(obj[i],
                            dRandReal() * 10 - 5, 4+(i/10), dRandReal() * 10 - 5);
        dRFromAxisAndAngle(R, dRandReal() * 2.0 - 1.0,
                            dRandReal() * 2.0 - 1.0,
                            dRandReal() * 2.0 - 1.0,
                            dRandReal() * M_PI*2 - M_PI);
        dBodySetRotation(obj[i], R);
        // set the bodies mass and the newly created geometry
        dGeomSetBody(geom, obj[i]);
        dBodySetMass(obj[i], &m);
    }
    
    makeStatic((Vector3){0,0,0}, (Vector3){20,1,20});
    makeStatic((Vector3){0,1,-9.5}, (Vector3){20,1,1});
    makeStatic((Vector3){9.5,1,0}, (Vector3){1,1,20});
    makeStatic((Vector3){-9.5,1,0}, (Vector3){1,1,20});
    
    Vector3 debug = {0};
    
    // keep the physics fixed time in step with the render frame
    // rate which we don't know in advance
    float frameTime = 0; 
    float physTime = 0;
    const float physSlice = 1.0 / 240.0;
    const int maxPsteps = 6;

    //--------------------------------------------------------------------------------------
    //
    // Main game loop
    //
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())            // Detect window close button or ESC key
    {
        //--------------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        bool spcdn = IsKeyDown(KEY_SPACE);
        
        const dReal* pos = dBodyGetPosition(obj[0]);
        debug.x = pos[0];
        debug.y = pos[1];
        debug.z = pos[2];
        
        for (int i = 0; i < numObj; i++) {
            const dReal* pos = dBodyGetPosition(obj[i]);
            if (spcdn) {
                // apply force if the space key is held
                const dReal* v = dBodyGetLinearVel(obj[i]);
                if (v[1] < 10 && pos[1]<10) { // cap upwards velocity and don't let it get too high
                    dBodyEnable (obj[i]); // case its gone to sleep
                    dMass mass;
                    dBodyGetMass (obj[i], &mass);
                    // give some object more force than others
                    float f = (16+(((float)i/numObj)*4)) * mass.mass;
                    dBodyAddForce(obj[i], rndf(-f,f), f*4, rndf(-f,f));
                }
            }

            
            if(pos[1]<-10) {
                // teleport back if fallen off the ground
                dBodySetPosition(obj[i], dRandReal() * 10 - 5,
                                        12 + rndf(1,2), dRandReal() * 10 - 5);
                dBodySetLinearVel(obj[i], 0, 0, 0);
                dBodySetAngularVel(obj[i], 0, 0, 0);
            }
        }
        
        // update the light shader with the camera view position
        updateShader(camera);

        frameTime += GetFrameTime();
        int pSteps = 0;
        physTime = GetTime(); 
        
        while (frameTime > physSlice) {
            // check for collisions
            // TODO use 2nd param data to pass custom structure with
            // world and space ID's to avoid use of globals...
            dSpaceCollide(space, 0, &nearCallback);
            
            // step the world
            dWorldQuickStep(world, physSlice);  // NB fixed time step is important
            dJointGroupEmpty(contactgroup);
            
            frameTime -= physSlice;
            pSteps++;
            if (pSteps > maxPsteps) {
                frameTime = 0;
                break;      
            }
        }
        
        physTime = GetTime() - physTime;    

        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
     
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
            
            // NB normally you wouldn't be drawing the collision meshes
            // instead you'd iterrate all the bodies get a user data pointer
            // from the body you'd previously set and use that to look up
            // what you are rendering oriented and positioned as per the
            // body
            drawAllSpaceGeoms(space);        
            DrawGrid(100, 1.0f);

        EndMode3D();

        if (pSteps > maxPsteps) DrawText("WARNING CPU overloaded lagging real time", 10, 0, 20, RED);
        DrawText(TextFormat("%2i FPS", GetFPS()), 10, 20, 20, WHITE);
        DrawText(TextFormat("debug %4.4f %4.4f %4.4f",debug.x,debug.y,debug.z), 10, 100, 20, WHITE);
        DrawText(TextFormat("Phys steps per frame %i",pSteps), 10, 120, 20, WHITE);
        DrawText(TextFormat("Phys time per frame %2.6f",physTime), 10, 140, 20, WHITE);
        DrawText(TextFormat("total time per frame %2.6f",frameTime), 10, 160, 20, WHITE);
        DrawText(TextFormat("Phys / frame %3.2f%",(frameTime/physTime)*100.0), 10, 180, 20, WHITE);
        
        DrawText(TextFormat("objects %i",numObj), 10, 200, 20, WHITE);

        EndDrawing();

    }
    //----------------------------------------------------------------------------------


    //--------------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    freeModels();

    dJointGroupEmpty(contactgroup);
    dJointGroupDestroy(contactgroup);
    dSpaceDestroy(space);
    dWorldDestroy(world);
    dCloseODE();

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    
    return 0;
}

