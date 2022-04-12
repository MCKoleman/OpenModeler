#pragma once
#include "fileHelper.h"
#include "meshModel.h"
#include "indexStructs.h"

void ReadObjFromFile(Mesh* mesh, std::string location, std::string fileName);
void BuildSMesh(SMesh* smesh, std::vector<FaceData>& tempFaces, std::unordered_map<std::string, Material>& tempMaterials, std::vector<IndVertex>& tempVertices, float scale);
void BuildIMesh(IMesh* imesh, std::vector<FaceData>& tempFaces, std::unordered_map<std::string, Material>& tempMaterials, std::vector<IndVertex>& tempVertices, float scale);