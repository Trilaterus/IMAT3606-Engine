#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Component.h"
#include "CPModel.h"
#include <iostream>
#include "CPControllable.h"
#include "CPCamera.h"

class GameObject
{
private:
	CPModel* m_pCPModel;
	CPCamera* m_pCPCamera;

public:
	GameObject();
	~GameObject();

	// attachcomponent
	void attachModel();
	void attachModel(std::string sModelName);
	void attachCamera();

	// dettachcomponent (?)


	// All component functions

	// MODEL

	void rotateModel(float fAngle, float fX, float fY, float fZ);
	void drawModel(sf::RenderWindow& window) const;
	void drawModel(sf::RenderWindow& window, sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const;
	void setModelAngle(float fXAngle, float fYAngle, float fZAngle);
	void moveModel(float fIncrement);
	void moveModel(float fXChange, float fYChange, float fZChange);
	void setModelPosition(float fXPos, float fYPos, float fZPos);

	// CAMERA

	sf::Vector3f getCameraPosition();
	sf::Vector3f getCameraAngle() const;
	void setCameraPosition(sf::Vector3f vPosition);
	void setCameraPosition(float fX, float fY, float fZ);
	void moveCamera(float fX, float fY, float fZ);
	void moveCameraForward(float fIncrement);
	void strafeCameraRight(float fIncrement);
	void setCameraAngle(sf::Vector3f vAngle);
	void setCameraAngle(float fX, float fY, float fZ);
	void rotateCamera(float fX, float fY, float fZ);

	// DUPLICATES 

	void update(sf::RenderWindow& window); // Model,
};

#endif // GAMEOBJECT_H