#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML\OpenGL.hpp>

class ObjectLoader
{
private:
public:
	std::string m_sFileName;
	std::vector<float> m_vfVertexCoordsIndex; // v
	std::vector<float> m_vfTextureNormalsIndex; // vt
	std::vector<float> m_vfVertexNormalsIndex; // vn

	std::vector<int> m_viFaceVIndex; // Hold indexes for Vertex co ordinates
	std::vector<int> m_viFaceTNIndex; // Holds indexes for Texture Normals
	std::vector<int> m_viFaceVNIndex; // Holds indexes for Vertex Normals

	std::vector<float> m_vfVertexCoords;
	std::vector<float> m_vfTextureNormals;
	std::vector<float> m_vfVertexNormals;

//public:
	ObjectLoader();
	ObjectLoader(std::string filename);
	ObjectLoader(std::string filename, bool load);

	std::vector<float> getVertexCoords(); // &
	std::vector<float> getTextureNormals(); // &
	std::vector<float> getVertexNormals(); // &

	float* getVertexCoordsFirst();
	float* getVertexNormsFirst();
	float* getVertexTextureFirst();

	std::vector<int>& getFaceVIndex();
	int* getFaceVIndexFirst();

	void setFilePath(std::string filename);

	bool loadObject();
};

#endif