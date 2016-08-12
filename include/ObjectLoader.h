/**
The ObjectLoader class allows for the vertices, normals and texture normals to be
parsed from varying layout of .obj files. Although called an ObjectLoader it in
itself holds the values of the object (It could do with a name refactor).
In this version the texture normals have been disabled to reduce risk of crashing.

@author Hussain */

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

	std::vector<int> m_viFaceVIndex; // Hold indexes for Vertex coordinates
	std::vector<int> m_viFaceTNIndex; // Holds indexes for Texture Normals
	std::vector<int> m_viFaceVNIndex; // Holds indexes for Vertex Normals

	std::vector<float> m_vfVertexCoords;
	std::vector<float> m_vfTextureNormals;
	std::vector<float> m_vfVertexNormals;

//public:
	/**
	The default constructor for the ObjectLoader class.
	If you are using this ensure to call setFilePath()
	and use loadObject() to load the objects data. */
	ObjectLoader();

	/**
	This constructor allows you to pass the file path
	for the object, but it does not load the object.
	Used for potential threading.
	@param sFilename A string that represents the location of the .obj file */
	ObjectLoader(std::string sFilename);

	/**
	This constructor saves the file path and immediatly attempts
	to load the object, printing appropriate error messages to
	the console if the object cannot be loaded.
	@param sFilename A string that represents the location of the .obj file
	@param bLoad A bool that indicates whether to load the object immediately */
	ObjectLoader(std::string sFilename, bool bLoad);

	/**
	Returns the vertex coordinates of the object.
	@return The vertex coordinates as a vector of floats */
	std::vector<float> getVertexCoords(); // &

	/**
	Returns the texture normals of the object.
	@return The texture normals as a vector of floats */
	std::vector<float> getTextureNormals(); // &

	/**
	Returns the vertex normals of the object.
	@return The vertex normals as a vector of floats */
	std::vector<float> getVertexNormals(); // &

	/**
	Returns a pointer to the first vertex coordinate in a vector.
	@return A pointer to a float which is the first vertex coordinate */
	float* getVertexCoordsFirst();

	/**
	Returns a pointer to the first vertex normal in a vector.
	@return A pointer to a float which is the first vertex normal */
	float* getVertexNormsFirst();

	/**
	Returns a pointer to the first vertex texture in a vector.
	@return A pointer to a float which is the first vertex texture */
	float* getVertexTextureFirst();

	/**
	Returns the entire face index.
	@return The entire face index as a vector of ints */
	std::vector<int>& getFaceVIndex();

	/**
	Returns a pointer to the first face index in a vector.
	@return A pointer to an int which is the first face index */
	int* getFaceVIndexFirst();

	/**
	Replaces the current file path value.
	@param sFilename A string that represents the location of the .obj */
	void setFilePath(std::string filename);

	/**
	Attempts to load the object, printing appropriate
	error messages to the console if the object cannot be loaded.
	Returns a true boolean if successful and a false if not.
	@return A boolean representing if the object loaded or not */
	bool loadObject();
};

#endif