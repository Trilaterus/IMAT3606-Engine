#include "objectLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/* CONSTRUCTORS */

ObjectLoader::ObjectLoader()
{

}

ObjectLoader::ObjectLoader(std::string filename)
{
	m_sFileName = filename;
}

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
			std::cout << "fail" << std::endl;
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
		if (m_vfTextureNormalsIndex.size() != 0)
		{
			for (std::vector<int>::iterator it = m_viFaceTNIndex.begin(); it != m_viFaceTNIndex.end(); ++it)
			{
				m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3));
				m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3 + 1));
				m_vfTextureNormals.push_back(m_vfTextureNormalsIndex.at((*it -1) * 3 + 2));
			}
		}
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
		std::cout << "File not loaded" << std::endl;
	}
}

/* FUNCTIONS */

std::vector<float> ObjectLoader::getVertexCoords()
{
	return m_vfVertexCoords;
}

std::vector<float> ObjectLoader::getTextureNormals()
{
	return m_vfTextureNormals;
}

std::vector<float> ObjectLoader::getVertexNormals()
{
	return m_vfVertexNormals;
}

float* ObjectLoader::getVertexCoordsFirst()
{
	return &m_vfVertexCoords.at(0);
}

float* ObjectLoader::getVertexNormsFirst()
{
	return &m_vfVertexNormals.at(0);
}

float* ObjectLoader::getVertexTextureFirst()
{
	return &m_vfTextureNormals.at(0);
}

std::vector<int>& ObjectLoader::getFaceVIndex()
{
	return m_viFaceVIndex;
}

int* ObjectLoader::getFaceVIndexFirst()
{
	return &m_viFaceVIndex.at(0);
}

void ObjectLoader::setFilePath(std::string filename)
{
	m_sFileName = filename;
}

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