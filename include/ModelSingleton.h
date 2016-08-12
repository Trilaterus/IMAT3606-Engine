/**
A singleton class which stores ObjectLoaders in order to ensure efficiency
when drawing and created Models or meshes.

@author Hussain */

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

	/**
	Returns the only instance of the ModelSingleton.
	@return The only instance of ModelSingleton	*/
	static ModelSingleton& instance();
	
	/**
	Loads and stores all the .objs from an XML file specified within
	the function. */
	void init();

	/**
	Loads a model from a passed file path and stores it with a passed ID.
	Returns a bool representing its success.
	@param sName A string ID for the .obj
	@param sFileName A string file path to the .obj file
	@return A bool representing the success of the load */
	bool loadModel(std::string sName, std::string sFileName); 

	/**
	Returns an object specified by a passed ID.
	@param sName The string ID of the object
	@return An ObjectLoader address related to the ID passed */
	ObjectLoader& getModel(std::string sName);
};

#endif