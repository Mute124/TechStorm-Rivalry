#pragma once
#include "Globals.h"

#include "lib/raylib.h"
#include "lib/raymath.h"


#include "Gameobj.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>


class TerrainTriangle : public GameObject {

private:

 
  // has to be long since there will be alot.
  long int m_id;
  const Shader shader;
  Model m_model;
  Mesh mesh;
  Color m_color;
  TriVert m_vert;
  
  Texture2D m_tex;
  
  Vector3 position;

public:
  
  TerrainTriangle(Shader shader, TriVert Verticies) : shader(shader), m_vert(Verticies) {
    
    this->m_tex = LoadTextureFromImage(GenImageColor(10, 10, GREEN));
    this->mesh = GenMeshCustom(Verticies);
    this->m_model = LoadModelFromMesh(this->mesh);
    this->m_model.materials[0].shader = shader;
    this->m_model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(this->shader, "viewPos");
    
    this->m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_tex;
    this->m_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].value = 10.0f;

    this->m_id = RegisterObj();
    this->m_vert = Verticies;

    this->position = (Vector3){this->m_vert.v1.x / 2,this->m_vert.v2.y / 2, this->m_vert.v3.z / 2 };
  }
  int GetType() const override { return 0; }
  void SetModel() const override {}

  void Draw() const override {

    DrawModel(this->m_model, this->position, 1.0f, RED);
    
  }
};