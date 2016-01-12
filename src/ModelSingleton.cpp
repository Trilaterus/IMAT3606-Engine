#include "ModelSingleton.h"

ModelSingleton::ModelSingleton()
{
	ObjectLoader object;
	object.setFilePath("resources/objs/default.obj");
	if (!object.loadObject())
	{
		std::cout << "ModelSingleton: Error loading default file!" << std::endl;
	}
	m_AllModels["default"] = object;
}

ModelSingleton& ModelSingleton::instance()
{
	static ModelSingleton instance;
	return instance;
}

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