#pragma once
#include "Gameobj.h"
#include "Globals.h"
#include "Triangle.h"
#include "lib/raylib.h"
#include "lib/raymath.h"
#include "SimpleGameObj.h"

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>

#ifndef SIDE_LENGTH
#define SIDE_LENGTH 1
#endif

Vector3 GenerateNormalizedPosition(Vector3 Vec1, int MaxDeviation);

class Grid : public SimpleGameObj
{
  public:
    void Draw() const override {
      for (int i = 0; i < WORLD_SIZE; i++) {
        
      }  
    }
    
    Grid() {
      for (int x = 0; x < WORLD_SIZE; x++) {
        for (int y = 0; y < WORLD_SIZE; y++) {

          this->Append(Vector3RandomEx(m_positions[iteration-2], m_positions[iteration-1]));
          
        }
        this->Append(Vector3RandomEx(m_positions[iteration-2], m_positions[iteration-1]));
      }
    }
    
    void Append(Vector3 Position) {
      iteration++;
      m_positions.push_back(RoundVec3(Position));
    }
    std::vector<Vector3> m_positions;
    
    int iteration; //How many times the list has been appended
};

class Generator {
  public:
    
    Generator() {}
    ~Generator() {
      delete grid;
      delete this;
    }
    
    // generates all the triangles and then poof
    void GenerateTerrain() {
      m_last.v1 = Vector3Random(0, 3);
      

      
    }
    
    
    
    int getTriCount() {
      return m_tricount;
      
    }
    
  private:
    int m_tricount;
    Grid *grid = new Grid();
    std::vector<GameObject *> objs;
    TriVert m_last;
};

CubeVerticies getGridParts(int Cube) {}



Vector3 GenerateNormalizedPosition(Vector3 Vec1, int MaxDeviation) {
  Vector3 result; // no value yet

  float x, y, z;

  x = GetRandomValue(Vec1.x, MaxDeviation);
  y = GetRandomValue(Vec1.x, MaxDeviation);
  z = GetRandomValue(Vec1.x, MaxDeviation);

  result = (Vector3){x, y, z};
  return result;
}