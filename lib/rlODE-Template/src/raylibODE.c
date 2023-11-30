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
#include "rlgl.h"

#include <ode/ode.h>
#include "raylibODE.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

Model box;
Model ball;
Model cylinder;

Texture crateTx;
Texture earthTx;
Texture drumTx;

Shader shader;

void updateShader(Camera camera) {
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position.x, SHADER_UNIFORM_VEC3);
}

void setupModels() {
    box = LoadModelFromMesh(GenMeshCube(1,1,1));
    ball = LoadModelFromMesh(GenMeshSphere(.5,32,32));
    // alas gen cylinder is wrong orientation for ODE...
    // so rather than muck about at render time just make one the right orientation
    cylinder = LoadModel("data/cylinder.obj");

    // texture the models
    crateTx = LoadTexture("data/crate.png");
    earthTx = LoadTexture("data/earth.png");
    drumTx = LoadTexture("data/drum.png");
    
    box.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = crateTx;
    ball.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = earthTx;
    cylinder.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = drumTx;
    
    shader = LoadShader("data/simpleLight.vs", "data/simpleLight.fs");
    // load a shader and set up some uniforms
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    
    // ambient light level
    int amb = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, amb, (float[4]){0.2,0.2,0.2,1.0}, SHADER_UNIFORM_VEC4);

    // models share the same shader
    box.materials[0].shader = shader;
    ball.materials[0].shader = shader;
    cylinder.materials[0].shader = shader;

    // using 4 point lights, white, red, green and blue
    Light lights[MAX_LIGHTS];
    (void)lights;

    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -25,25,25 }, Vector3Zero(),
                    (Color){128,128,128,255}, shader);
    lights[1] = CreateLight(LIGHT_POINT, (Vector3){ -25,25,-25 }, Vector3Zero(),
                    (Color){64,64,64,255}, shader);
/*                    
    lights[2] = CreateLight(LIGHT_POINT, (Vector3){ -25,25,-25 }, Vector3Zero(),
                    GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, (Vector3){ -25,25,25 }, Vector3Zero(),
                    BLUE, shader);
*/            
}

void freeModels() {
    UnloadModel(box);
    UnloadTexture(crateTx);
    UnloadModel(ball);
    UnloadTexture(earthTx);
    UnloadModel(cylinder);
    UnloadTexture(drumTx);
    UnloadShader(shader);
}

// reused for all geoms that don't collide
// ie vehicle counter weights
static geomInfo disabled;

// optionally a geom can have user data, in this case
// the only info our user data has is if the geom
// should collide or not
// this allows for bodies that effect COG without
// colliding
bool checkColliding(dGeomID g)
{
    geomInfo* gi = (geomInfo*)dGeomGetData(g);
    if (!gi) return true;
    return gi->collidable;
}

// position rotation scale all done with the models transform...
void MyDrawModel(Model model, Color tint)
{
    for (int i = 0; i < model.meshCount; i++)
    {
        Color color = model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color;

        Color colorTint = WHITE;
        colorTint.r = (unsigned char)((((float)color.r/255.0)*((float)tint.r/255.0))*255.0f);
        colorTint.g = (unsigned char)((((float)color.g/255.0)*((float)tint.g/255.0))*255.0f);
        colorTint.b = (unsigned char)((((float)color.b/255.0)*((float)tint.b/255.0))*255.0f);
        colorTint.a = (unsigned char)((((float)color.a/255.0)*((float)tint.a/255.0))*255.0f);

        model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = colorTint;
        DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], model.transform);
        model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = color;
    }
}


// these two just convert to column major and minor
void rayToOdeMat(Matrix* m, dReal* R) 
{
    R[ 0] = m->m0;   R[ 1] = m->m4;   R[ 2] = m->m8;    R[ 3] = 0;
    R[ 4] = m->m1;   R[ 5] = m->m5;   R[ 6] = m->m9;    R[ 7] = 0;
    R[ 8] = m->m2;   R[ 9] = m->m6;   R[10] = m->m10;   R[11] = 0;
    R[12] = 0;       R[13] = 0;       R[14] = 0;        R[15] = 1;   
}

// sets a raylib matrix from an ODE rotation matrix
void odeToRayMat(const dReal* R, Matrix* m)
{
    m->m0 = R[0];  m->m1 = R[4];  m->m2 = R[8];      m->m3 = 0;
    m->m4 = R[1];  m->m5 = R[5];  m->m6 = R[9];      m->m7 = 0;
    m->m8 = R[2];  m->m9 = R[6];  m->m10 = R[10];    m->m11 = 0;
    m->m12 = 0;    m->m13 = 0;    m->m14 = 0;        m->m15 = 1;
}

void drawGeom(dGeomID geom) 
{
    const dReal* pos = dGeomGetPosition(geom);
    const dReal* rot = dGeomGetRotation(geom);
    int class = dGeomGetClass(geom);
    Model* m = 0;
    dVector3 size;
    if (class == dBoxClass) {
        m = &box;
        dGeomBoxGetLengths(geom, size);
    } else if (class == dSphereClass) {
        m = &ball;
        float r = dGeomSphereGetRadius(geom);
        size[0] = size[1] = size[2] = (r*2);
    } else if (class == dCylinderClass) {
        m = &cylinder;
        dReal l,r;
        dGeomCylinderGetParams (geom, &r, &l);
        size[0] = size[1] = r*2;
        size[2] = l;
    }
    if (!m) return;
    
    Matrix matScale = MatrixScale(size[0], size[1], size[2]);
    Matrix matRot;
    odeToRayMat(rot, &matRot);
    Matrix matTran = MatrixTranslate(pos[0], pos[1], pos[2]);
    
    m->transform = MatrixMultiply(MatrixMultiply(matScale, matRot), matTran);
    
    dBodyID b = dGeomGetBody(geom);
    Color c = WHITE;
    if (b) if (!dBodyIsEnabled(b)) c = RED;

    MyDrawModel(*m, c);
    m->transform = MatrixIdentity();
}

void drawAllSpaceGeoms(dSpaceID space) 
{
    int ng = dSpaceGetNumGeoms(space);
    for (int i=0; i<ng; i++) {
        dGeomID geom = dSpaceGetGeom(space, i);
        if (checkColliding(geom))  
        {
            // hide non colliding geoms (car counter weights)
            drawGeom(geom);
        }
    }
}


vehicle* CreateVehicle(dSpaceID space, dWorldID world)
{
    // TODO these should be parameters
    Vector3 carScale = (Vector3){2.5, 0.5, 1.4};
    float wheelRadius = 0.5, wheelWidth = 0.45;
    
    vehicle* car = RL_MALLOC(sizeof(vehicle));
    
    // car body
    dMass m;
    dMassSetBox(&m, 1, carScale.x, carScale.y, carScale.z);  // density
    dMassAdjust(&m, 550); // mass
    
    car->bodies[0] = dBodyCreate(world);
    dBodySetMass(car->bodies[0], &m);
    dBodySetAutoDisableFlag( car->bodies[0], 0 );


    car->geoms[0] = dCreateBox(space, carScale.x, carScale.y, carScale.z);
    dGeomSetBody(car->geoms[0], car->bodies[0]);
    
    // TODO used a little later and should be a parameter
    dBodySetPosition(car->bodies[0], 15, 6, 15.5);
    
    dGeomID front = dCreateBox(space, 0.5, 0.5, 0.5);
    dGeomSetBody(front, car->bodies[0]);
    dGeomSetOffsetPosition(front, carScale.x/2-0.25, carScale.y/2+0.25 , 0);
    
    car->bodies[5] = dBodyCreate(world);
    dBodySetMass(car->bodies[5], &m);
    dBodySetAutoDisableFlag( car->bodies[5], 0 );
    // see previous TODO
    dBodySetPosition(car->bodies[5], 15, 6-2, 15.5);
    car->geoms[5] = dCreateSphere(space,1);
    dGeomSetBody(car->geoms[5],car->bodies[5]);
    disabled.collidable = false;
    dGeomSetData(car->geoms[5], &disabled);
    
    car->joints[5] = dJointCreateFixed (world, 0);
    dJointAttach(car->joints[5], car->bodies[0], car->bodies[5]);
    dJointSetFixed (car->joints[5]);
    
    // wheels
    dMassSetCylinder(&m, 1, 3, wheelRadius, wheelWidth);
    dMassAdjust(&m, 2); // mass
    dQuaternion q;
    dQFromAxisAndAngle(q, 0, 0, 1, M_PI * 0.5);
    for(int i = 1; i <= 4; ++i)
    {
        car->bodies[i] = dBodyCreate(world);
        dBodySetMass(car->bodies[i], &m);
        dBodySetQuaternion(car->bodies[i], q);
        car->geoms[i] = dCreateCylinder(space, wheelRadius, wheelWidth);
        dGeomSetBody(car->geoms[i], car->bodies[i]);
        dBodySetFiniteRotationMode( car->bodies[i], 1 );
            dBodySetAutoDisableFlag( car->bodies[i], 0 );
    }

    const dReal* cp = dBodyGetPosition(car->bodies[0]);
    // TODO wheel base and axel width should be parameters
    dBodySetPosition(car->bodies[1], cp[0]+1.2, cp[1]-.5, cp[2]-1); 
    dBodySetPosition(car->bodies[2], cp[0]+1.2, cp[1]-.5, cp[2]+1); 
    dBodySetPosition(car->bodies[3], cp[0]-1.2, cp[1]-.5, cp[2]-1); 
    dBodySetPosition(car->bodies[4], cp[0]-1.2, cp[1]-.5, cp[2]+1); 

    // hinge2 (combined steering / suspension / motor !)
    for(int i = 0; i < 4; ++i)
    {
        car->joints[i] = dJointCreateHinge2(world, 0);
        dJointAttach(car->joints[i], car->bodies[0], car->bodies[i+1]);
        const dReal* wPos = dBodyGetPosition(car->bodies[i+1]);
        dJointSetHinge2Anchor(car->joints[i], wPos[0], wPos[1], wPos[2]);
        
        dReal axis1[] = { 0, -1, 0 };
        dReal axis2[] = { 0, 0, ((i % 2) == 0) ? -1 : 1};
        
        // replacement for deprecated calls
        dJointSetHinge2Axes (car->joints[i], axis1, axis2);
        //dJointSetHinge2Axis1(joints[i], 0, 1, 0);
        //dJointSetHinge2Axis2(joints[i], 0, 0, ((i % 2) == 0) ? -1 : 1);

        dJointSetHinge2Param(car->joints[i], dParamLoStop, 0);
        dJointSetHinge2Param(car->joints[i], dParamHiStop, 0);
        dJointSetHinge2Param(car->joints[i], dParamLoStop, 0);
        dJointSetHinge2Param(car->joints[i], dParamHiStop, 0);
        dJointSetHinge2Param(car->joints[i], dParamFMax, 1500);

        dJointSetHinge2Param(car->joints[i], dParamVel2, dInfinity);
        dJointSetHinge2Param(car->joints[i], dParamFMax2, 1500);

        dJointSetHinge2Param(car->joints[i], dParamSuspensionERP, 0.9);
        dJointSetHinge2Param(car->joints[i], dParamSuspensionCFM, 0.002);

        // steering
        if (i<2) {
            dJointSetHinge2Param (car->joints[i],dParamFMax,500);
            dJointSetHinge2Param (car->joints[i],dParamLoStop,-0.5);
            dJointSetHinge2Param (car->joints[i],dParamHiStop,0.5);
            dJointSetHinge2Param (car->joints[i],dParamLoStop,-0.5);
            dJointSetHinge2Param (car->joints[i],dParamHiStop,0.5);
            dJointSetHinge2Param (car->joints[i],dParamFudgeFactor,0.1);
        }
        
    }
    // disable motor on front wheels
    dJointSetHinge2Param(car->joints[0], dParamFMax2, 0);
    dJointSetHinge2Param(car->joints[1], dParamFMax2, 0);

    return car;
}


void updateVehicle(vehicle *car, float accel, float maxAccelForce, 
                    float steer, float steerFactor)
{
    float target;
    target = 0;
    if (fabs(accel) > 0.1) target = maxAccelForce;
    //dJointSetHinge2Param( car->joints[0], dParamVel2, -accel );
    //dJointSetHinge2Param( car->joints[1], dParamVel2, accel );
    dJointSetHinge2Param( car->joints[2], dParamVel2, -accel );
    dJointSetHinge2Param( car->joints[3], dParamVel2, accel );

    //dJointSetHinge2Param( car->joints[0], dParamFMax2, target );
    //dJointSetHinge2Param( car->joints[1], dParamFMax2, target );
    dJointSetHinge2Param( car->joints[2], dParamFMax2, target );
    dJointSetHinge2Param( car->joints[3], dParamFMax2, target );
    
    for(int i=0;i<2;i++) {
        dReal v = steer - dJointGetHinge2Angle1 (car->joints[i]);
        v *= steerFactor;
        dJointSetHinge2Param (car->joints[i],dParamVel,v);
    }
}    

void unflipVehicle (vehicle *car)
{
    const dReal* cp = dBodyGetPosition(car->bodies[0]);
    dBodySetPosition(car->bodies[0], cp[0], cp[1]+2, cp[2]);

    const dReal* R = dBodyGetRotation(car->bodies[0]);
    dReal newR[16];
    dRFromEulerAngles(newR, 0, -atan2(-R[2],R[0]) , 0);
    dBodySetRotation(car->bodies[0], newR);
    
    // wheel offsets
    // TODO make configurable & use in vehicle set up 
    dReal wheelOffsets[4][3] = {
           { +1.2, -.6, -1 },
           { +1.2, -.6, +1 },
           { -1.2, -.6, -1 },
           { -1.2, -.6, +1 }
        };

    for (int i=1; i<5; i++) {
        dVector3 pb;
        dBodyGetRelPointPos(car->bodies[0], wheelOffsets[i-1][0], wheelOffsets[i-1][1], wheelOffsets[i-1][2], pb);
        dBodySetPosition(car->bodies[i], pb[0], pb[1], pb[2]);
    }

}
