/** \file ObjectLoader.cpp
The ObjectLoader class allows for the vertices, normals and texture normals to be
parsed from varying layout of .obj files. Although called an ObjectLoader it in
itself holds the values of the object. In this version the texture normals have
been disabled to reduce risk of crashing.
*/

#include "objectLoader.h"

/**
The default constructor for the ObjectLoader class.
If you are using this ensure to call setFilePath()
and use loadObject() to load the objects data.
*/
ObjectLoader::ObjectLoader()
{

}

/**
This constructor allows you to pass the file path
for the object, but it does not load the object.
Used for potential threading.

\param sFilename A string that represents the location of the .obj file
*/
ObjectLoader::ObjectLoader(std::string sFilename)
{
	m_sFileName = sFilename;
}

/**
This constructor saves the file path and immediatly attempts
to load the object, printing appropriate error messages to
the console if the object cannot be loaded.
*/
ObjectLoader::ObjectLoader(std::string filename, bool load)
{
	if (load && !filename.empty())
	{
		std::ifstream model (filename, std::ifstream::ios_base::in);

		if (model.is_open())
		{
			std::string line;
			while (getline(model, line))
			{
				std::string s;
				std::string sp; // Peeked at line
				std::istringstream is(line);

				is >> s; // read first chunk
				sp = is.peek();

				if (s == "v")
				{
					float value;

					while (is >> value)
					{
						m_vfVertexCoordsIndex.push_back(value);
					}
				}

				else if (s == "vn")
				{
					float value;

					while (is >> value)
					{
						m_vfVertexNormalsIndex.push_back(value);
					}
				}

				else if (s == "vt")
				{
					float value;

					while (is >> value)
					{
						m_vfTextureNormals.push_back(value);
					}
				}
			
				else if (s == "f")
				{
					int value;

					while (is >> value)
					{
						if (is.peek() == '/') // a//b
						{
							//  here format is  either v//vn  or v/vt/vn

							m_viFaceVIndex.push_back(value); // pushes back first number
							is.get(); // reads number so current char is '/'
							if(is.peek() == '/')
							{
								// here format is v // vn
								
								is.get();
								is >> value;
								m_viFaceVNIndex.push_back(value);
							}
							else // a/b/c  format is v / vt / vn
							{
								is >> value;
								m_viFaceTNIndex.push_back(value);
								is.get();
								is >> value;
								m_viFaceVNIndex.push_back(value);
							}
						}
						else // a b c
						{
							m_viFaceVIndex.push_back(value);
							is >> value;
							m_viFaceTNIndex.push_back(value);
							is >> value;
							m_viFaceVNIndex.push_back(value);
						}
						// No handling for a/b (vertex coord & texture normal)
					}
				}
				else
				{
					// If letter is unknown skip line
				}
			}
		}
		else
		{
			model.close();
		}

		/* CONVERT FILE STUFF INTO ARRAY */

		if (m_vfVertexCoordsIndex.size() != 0)
		{
			for (std::vector<int>::iterator it = m_viFaceVIndex.begin(); it != m_viFaceVIndex.end(); ++it)
			{
				m_vfVertexCoords.push_back(m_vfVertexCoordsIndex.at(((*it) -1) * 3));
				m_vfVertexCoords.push_back(m_vfVertexCoordsIndex.at(((*it) -1) * 3 + 1));
				m_vfVertexCoords.push_back(m_vfVertexCoordsIndex.at(((*it) -1) * 3 + 2));
			}
		}
		/* This is where texture normals would be stored... since I have no textures I've commented it out
		if (m_vfTextureNormalsIndex.size() != 0)
		{
			for (std::vector<int>::iterator it = m_viFaceTNIndex.begin(); it != m_viFaceTNIndex.end(); ++it)
			{
				m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3));
				m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3 + 1));
				m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3 + 2));
			}
		}
		*/
		if (m_vfVertexNormalsIndex.size() != 0)
		{
			for (std::vector<int>::iterator it = m_viFaceVNIndex.begin(); it != m_viFaceVNIndex.end(); ++it)
			{
				m_vfVertexNormals.push_back(m_vfVertexNormalsIndex.at((*it -1) * 3));
				m_vfVertexNormals.push_back(m_vfVertexNormalsIndex.at((*it -1) * 3 + 1));
				m_vfVertexNormals.push_back(m_vfVertexNormalsIndex.at((*it -1) * 3 + 2));
			}
		}
	}
	else
	{
		std::cout << "ObjectLoader: Error file path empty or incorrect!" << std::endl;
	}
}

/**
Returns the vertex coordinates of the object.

\return The vertex coordinates as a vector of floats.
*/
std::vector<float> ObjectLoader::getVertexCoords()
{
	return m_vfVertexCoords;
}

/**
Returns the texture normals of the object.

\return The texture normals as a vector of floats.
*/
std::vector<float> ObjectLoader::getTextureNormals()
{
	return m_vfTextureNormals;
}

/**
Returns the vertex normals of the object.

\return The vertex normals as a vector of floats.
*/
std::vector<float> ObjectLoader::getVertexNormals()
{
	return m_vfVertexNormals;
}

/**
Returns a pointer to the first vertex coordinate in a vector.

\return A pointer to a float which is the first vertex coordinate.
*/
float* ObjectLoader::getVertexCoordsFirst()
{
	return &m_vfVertexCoords.at(0);
}

/**
Returns a pointer to the first vertex normal in a vector.

\return A pointer to a float which is the first vertex normal.
*/
float* ObjectLoader::getVertexNormsFirst()
{
	return &m_vfVertexNormals.at(0);
}

/**
Returns a pointer to the first vertex texture in a vector.

\return A pointer to a float which is the first vertex texture.
*/
float* ObjectLoader::getVertexTextureFirst()
{
	return &m_vfTextureNormals.at(0);
}

/**
Returns the entire face index.

\return The entire face index as a vector of ints.
*/
std::vector<int>& ObjectLoader::getFaceVIndex()
{
	return m_viFaceVIndex;
}

/**
Returns a pointer to the first face index in a vector.

\return A pointer to an int which is the first face index.
*/
int* ObjectLoader::getFaceVIndexFirst()
{
	return &m_viFaceVIndex.at(0);
}

/**
Replaces the current file path value.

\param sFilename A string that represents the location of the .obj
*/
void ObjectLoader::setFilePath(std::string sFilename)
{
	m_sFileName = sFilename;
}

/**
Attempts to load the object, printing appropriate
error messages to the console if the object cannot be loaded.
Returns a true boolean if successful and a false if not.

\return A boolean representing if the object loaded or not.
*/
bool ObjectLoader::loadObject()
{
	if (!m_sFileName.empty())
	{
		std::ifstream model (m_sFileName, std::ifstream::ios_base::in);

		if (model.is_open())
		{
			std::string line;
			while (getline(model, line))
			{
				std::string s;
				std::string sp; // Peeked at line
				std::istringstream is(line);

				is >> s; // read first chunk
				sp = is.peek();

				if (s == "v")
				{
					float value;

					while (is >> value)
					{
						m_vfVertexCoordsIndex.push_back(value);
					}
				}

				else if (s == "vn")
				{
					float value;

					while (is >> value)
					{
						m_vfVertexNormalsIndex.push_back(value);
					}
				}

				else if (s == "vt")
				{
					float value;

					while (is >> value)
					{
						m_vfTextureNormals.push_back(value);
					}
				}
			
				else if (s == "f")
				{
					int value;

					while (is >> value)
					{
						if (is.peek() == '/') // a//b
						{
							m_viFaceVIndex.push_back(value); // pushes back first number
							is.get(); // reads number so current char is '/'
							if(is.peek() == '/')
							{
								is.get();
								is >> value;
								m_viFaceVNIndex.push_back(value);
							}
							else // a/b/c
							{
								is >> value;
								m_viFaceTNIndex.push_back(value);
								is.get();
								is >> value;
								m_viFaceVNIndex.push_back(value);
							}
						}
						else // a b c
						{
							m_viFaceVIndex.push_back(value);
							is >> value;
							m_viFaceTNIndex.push_back(value);
							is >> value;
							m_viFaceVNIndex.push_back(value);
						}
						// No handling for a/b (vertex coord & texture normal)
					}
				}
			}
		}
		else
		{
			std::cout << "fail" << std::endl;
			model.close();
			return false;
		}

		/* CONVERT FILE STUFF INTO ARRAY */

		for (std::vector<int>::iterator it = m_viFaceVIndex.begin(); it != m_viFaceVIndex.end(); ++it)
		{
			m_vfVertexCoords.push_back(m_vfVertexCoordsIndex.at((*it -1) * 3));
			m_vfVertexCoords.push_back(m_vfVertexCoordsIndex.at((*it -1) * 3 + 1));
			m_vfVertexCoords.push_back(m_vfVertexCoordsIndex.at((*it -1) * 3 + 2));
		}
		/* This is where texture normals would be stored... since I have no textures I've commented it out
		for (std::vector<int>::iterator it = m_viFaceTNIndex.begin(); it != m_viFaceTNIndex.end(); ++it)
		{
			m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3));
			m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3 + 1));
			m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3 + 2));
		}
		*/
		for (std::vector<int>::iterator it = m_viFaceVNIndex.begin(); it != m_viFaceVNIndex.end(); ++it)
		{
			m_vfVertexNormals.push_back(m_vfVertexNormalsIndex.at((*it -1) * 3));
			m_vfVertexNormals.push_back(m_vfVertexNormalsIndex.at((*it -1) * 3 + 1));
			m_vfVertexNormals.push_back(m_vfVertexNormalsIndex.at((*it -1) * 3 + 2));
		}
		return true;
	}
	else
	{
		std::cout << "File not loaded" << std::endl;
		return false;
	}
}