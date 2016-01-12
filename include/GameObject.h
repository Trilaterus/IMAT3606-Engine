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
	void attachModel(std::string sModelName);
	void attachControllable();

	// dettachcomponent (?)


	// All component functions including duplicates

	void rotateModel(float fAngle, float fX, float fY, float fZ); // Model,
	void drawModel(sf::RenderWindow& window) const; // Model,
	void setAngle(float fXAngle, float fYAngle, float fZAngle); // Model,
	void move(float fIncrement); // Model,
	void move(float fXChange, float fYChange, float fZChange); // Model,
	void setPosition(float fXPos, float fYPos, float fZPos); // Model,

	void update(sf::RenderWindow& window); // Model,
	void draw(sf::RenderWindow& window) const; // Model,
};

#endif // GAMEOBJECT_H