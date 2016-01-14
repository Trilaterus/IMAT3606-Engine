#ifndef MODELSINGLETON_H
#define MODELSINGLETON_H

#include "ObjectLoader.h"
#include <map>
#include <iostream>
#include <msxml.h>
#include "TinyXML\tinyxml2.h"

class ModelSingleton // This is a singleton class
{
private:
	ModelSingleton();
	ModelSingleton(ModelSingleton& const);
	void operator=(ModelSingleton& const);

	std::map<std::string, ObjectLoader> m_AllModels;

public:
	static ModelSingleton& instance(); // get instance of ModelSingleton
	
	void init();
	bool loadModel(std::string sName, std::string sFileName); // save model to singleton under a specified name
	ObjectLoader& getModel(std::string sName); // get model by name
};

#endif