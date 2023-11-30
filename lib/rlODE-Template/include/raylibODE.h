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



// TODO extern for now - need to add function set these and keep them here...
extern Model ball;
extern Model box;
extern Model cylinder;

// 0 chassis / 1-4 wheel / 5 anti roll counter weight
typedef struct vehicle {
    dBodyID bodies[6];
    dGeomID geoms[6];
    dJointID joints[6];
} vehicle;

typedef struct geomInfo {
    
    bool collidable;
} geomInfo ;


void setupModels();
void freeModels();
void updateShader(Camera camera);
void rayToOdeMat(Matrix* mat, dReal* R);
void odeToRayMat(const dReal* R, Matrix* matrix);
void drawAllSpaceGeoms(dSpaceID space);
void drawGeom(dGeomID geom);
vehicle* CreateVehicle(dSpaceID space, dWorldID world);
void updateVehicle(vehicle *car, float accel, float maxAccelForce, 
                    float steer, float steerFactor);
void unflipVehicle (vehicle *car);
bool checkColliding(dGeomID g);
