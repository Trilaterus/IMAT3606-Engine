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
	~GameObject();

	// attachcomponent
	void attachModel();
	void attachControllable();

	// dettachcomponent (?)


	// All component functions including duplicates
	void rotateModel(float fAngle, float fX, float fY, float fZ); // Model,

	void update(sf::RenderWindow& window); // Model,
	void draw(sf::RenderWindow& window) const; // Model,
};

#endif // GAMEOBJECT_H