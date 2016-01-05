#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Component.h"
#include "CPModel.h"
#include <iostream>
#include "CPControllable.h"

class GameObject
{
private:
	CPModel* m_pCPModel;
	CPControllable* m_pCPControllable;

public:
	GameObject();

	// attachcomponent
	void attachControllable();

	// dettachcomponent (?)


	// All component functions including duplicates
	int onKeyPress(); // CPControllable
};

#endif // GAMEOBJECT_H