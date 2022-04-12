#pragma once
#include "fileHelper.h"
#include "indexStructs.h"

void ReadObjFromFile(Mesh* mesh, std::string location, std::string fileName);
void BuildMesh(Mesh* mesh, std::vector<FaceData>& tempFaces, std::unordered_map<std::string, Material>& tempMaterials, std::vector<IndVertex>& tempVertices, float scale);