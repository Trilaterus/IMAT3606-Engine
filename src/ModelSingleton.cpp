/** \file ModelSingleton.cpp
A singleton class which stores ObjectLoaders in order to ensure efficiency
when drawing and created Models or meshes.
*/
#include "ModelSingleton.h"

/**
The private default constructor for the class.
*/
ModelSingleton::ModelSingleton()
{

}

/**
Returns the only instance of the ModelSingleton.

\return The only instance of ModelSingleton
*/
ModelSingleton& ModelSingleton::instance()
{
	static ModelSingleton instance;
	return instance;
}

/**
Loads and stores all the .objs from an XML file specified within
the function.
*/
void ModelSingleton::init()
{
	tinyxml2::XMLDocument ModelXML;
	if (ModelXML.LoadFile("resources/xml/ModelMeshXML.xml"))
	{
		std::cout << "ModelSingleton: Error opening XML file!" << std::endl;
	}
	tinyxml2::XMLElement* eDocument = ModelXML.FirstChildElement("document");
	if (eDocument)
	{
		tinyxml2::XMLElement* eModel = eDocument->FirstChildElement("model");
		bool bParsing = true;
		while (bParsing)
		{
			if (eModel)
			{
				std::string sID;
				std::string sFilePath;

				// Get model ID
				tinyxml2::XMLElement* eID = eModel->FirstChildElement("id");
				if (eID)
				{
					sID = eID->GetText();
				}

				// Get model FilePath
				tinyxml2::XMLElement* eFilePath = eModel->FirstChildElement("filepath");
				if (eFilePath)
				{
					sFilePath = eFilePath->GetText();
				}

				// Check both strings to ensure neither are empty
				if (sID != "" ||
					sFilePath != "")
				{
					// Load model using information retrieved into ModelSinglton
					ObjectLoader object;
					object.setFilePath(sFilePath);
					if (!object.loadObject())
					{
						std::cout << "ModelSingleton: Error loading object!" << std::endl;
					}
					m_AllModels[sID] = object;
				}
				else
				{
					std::cout << "ModelSingleton: Empty text sections in XML!" << std::endl;
				}

				eModel = eModel->NextSiblingElement("model");
			}
			else
			{
				// No more <model>s found, end parsing
				bParsing = false;
			}
		}
	}
}

/**
Loads a model from a passed file path and stores it with a passed ID.
Returns a bool representing its success.

\param sName A string ID for the .obj
\param sFileName A string file path to the .obj file.
\return A bool representing the success of the load.
*/
bool ModelSingleton::loadModel(std::string sName, std::string sFileName)
{
	ObjectLoader object;
	object.setFilePath(sFileName);
	if (!object.loadObject())
	{
		std::cout << "ModelSingleton: Error loading from - " << sFileName << std::endl;
		return false;
	}
	else
	{
		m_AllModels[sName] = object;
		return true;
	}
}

/**
Returns an object specified by a passed ID.

\param sName The string ID of the object
\return An ObjectLoader address related to the ID passed.
*/
ObjectLoader& ModelSingleton::getModel(std::string sName)
{
	if (m_AllModels.find(sName) == m_AllModels.end())
	{
		// Not found
		return m_AllModels["default"];
	}
	else
	{
		// Found
		return m_AllModels[sName];
	}
}