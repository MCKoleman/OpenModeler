#include "objWriter.h"

void WriteObjToFile(Scene* scene, std::string location, std::string fileName)
{
	// Avoid overwriting files
	std::string objLoc = location + fileName + ".obj";
	int counter = 0;
	while (FileExists(objLoc)) {
		objLoc = location + fileName + "_" + std::to_string(counter) + ".obj";
		counter++;
	}

	Mesh* mesh = scene->GetCurMesh();
	auto verts = mesh->GetVerts();
	auto tris = mesh->GetTris();

    // Open the object
	// ---------------
    std::ofstream objFile;
    objFile.open(objLoc);

	// Write header
	// ------------
	objFile << "##\n";
	objFile << "## " << fileName << ".obj\n";
	objFile << "##\n";
	objFile << "## This file was generated using the OpenModeler program\n";
	objFile << "## created by Manu Kristian Kolehmainen and Andres Maldonado-Martin.\n";
	objFile << "## There is no copyright attributed to this file.\n";
	objFile << "##\n";
	objFile << "\n";

	// Write material
	// --------------
	//objFile << "mtllib " << fileName << ".mtl\n";
	//objFile << "usemtl default\n\n";

	// Write vertices
	// --------------
	int vertsSize = (int)verts.size();
	bool anyTexts = false;
	for (int i = 0; i < vertsSize; i++)
	{
		// Search for any texture information
		if (verts[i].texture != glm::vec3())
			anyTexts = true;

		glm::vec3 pos = verts[i].pos;
		objFile << "v " << RoundToPrecision(pos.x, 6) << " " << RoundToPrecision(pos.y, 6) << " " << RoundToPrecision(pos.z, 6) << "\n";
	}
	objFile << "# " << vertsSize << " vertices\n\n";

	// Write vertex normals
	// --------------------
	for (int i = 0; i < vertsSize; i++)
	{
		glm::vec3 norm = verts[i].normal;
		objFile << "vn " << RoundToPrecision(norm.x, 6) << " " << RoundToPrecision(norm.y, 6) << " " << RoundToPrecision(norm.z, 6) << "\n";
	}
	objFile << "# " << vertsSize << " vertex normals\n\n";

	// Write vertex textures only if needed
	// ------------------------------------
	int vertTextSize = 0;
	if (anyTexts) {
		vertTextSize = vertsSize;
		for (int i = 0; i < vertsSize; i++)
		{
			glm::vec3 text = verts[i].texture;
			objFile << "vt " << RoundToPrecision(text.x, 6) << " " << RoundToPrecision(text.y, 6) << " " << RoundToPrecision(text.z, 6) << "\n";
		}
	}
	objFile << "# " << vertTextSize << " texture vertices\n\n";

	// Write faces
	// -----------
	objFile << "g default\n";
	int trisSize = (int)tris.size();
	for (int i = 0; i < trisSize; i++)
	{
		auto triVerts = tris[i].vertices;

		// Store texture data if it is used
		if (anyTexts) {
			objFile << "f " <<	triVerts[0] << "/" << triVerts[0] << "/" << triVerts[0] << " ";
			objFile <<			triVerts[1] << "/" << triVerts[1] << "/" << triVerts[1] << " ";
			objFile <<			triVerts[2] << "/" << triVerts[2] << "/" << triVerts[2] << "\n";
		}
		// Only store normal and vertex data if there are no textures
		else {
			objFile << "f " <<	triVerts[0] << "//" << triVerts[0] << " ";
			objFile <<			triVerts[1] << "//" << triVerts[1] << " ";
			objFile <<			triVerts[2] << "//" << triVerts[2] << "\n";
		}
	}
	objFile << "# " << trisSize << " faces\n\n";

	// Write material groups
	// ---------------------

	// Close file
	// ----------
	objFile.close();
}

void WriteMtlToFile(Material* mat, std::string location, std::string fileName)
{
	std::string mtlLoc = location + fileName + ".mtl";

	// Open the object
	std::ofstream mtlFile;
	mtlFile.open(mtlLoc);

	// Write header
	mtlFile << "##\n";
	mtlFile << "## " << fileName << ".mtl\n";
	mtlFile << "##\n";
	mtlFile << "## This file was generated using the OpenModeler program\n";
	mtlFile << "## created by Manu Kristian Kolehmainen and Andres Maldonado-Martin.\n";
	mtlFile << "## There is no copyright attributed to this file.\n";
	mtlFile << "##\n";
	mtlFile << "\n";

	// Close file
	mtlFile.close();
}

void WriteMtlToFile(MaterialStorage* mat, std::string location, std::string fileName)
{
	std::string mtlLoc = location + fileName + ".mtl";
	// Open the object
	std::ofstream mtlFile;
	mtlFile.open(mtlLoc);

	// Write header
	mtlFile << "##\n";
	mtlFile << "## " << fileName << ".mtl\n";
	mtlFile << "##\n";
	mtlFile << "## This file was generated using the OpenModeler program\n";
	mtlFile << "## created by Manu Kristian Kolehmainen and Andres Maldonado-Martin.\n";
	mtlFile << "## There is no copyright attributed to this file.\n";
	mtlFile << "##\n";
	mtlFile << "\n";

	// Close file
	mtlFile.close();
}