/**
The GameObject class allows components to be attached to it in
order to create a data driven and flexible system.

@author Hussain */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Component.h"
#include "CPModel.h"
#include <iostream>
#include "CPControllable.h"
#include "CPCamera.h"
#include "CPLightSource.h"

class GameObject
{
private:
	CPModel* m_pCPModel;
	CPCamera* m_pCPCamera;
	CPLightSource* m_pCPLight;

public:
	GameObject();
	~GameObject();

	// Game Object functions //

	/**
	Checks whether the GameObject has a CPModel attached.
	\return True if a CPModel is attached */
	bool hasModel();

	/**
	Checks whether the GameObject has a CPCamera attached.
	\return True if a CPCamera is attached */
	bool hasCamera();

	/**
	Checks whether the GameObject has a CPLightSource attached.
	\return True if a CPLightSource is attached */
	bool hasLight();

	// attachComponent functions //

	/**
	Attaches a new instance of a CPModel onto the GameObject. */
	void attachModel();

	/**
	Attaches a new instance of a CPModel onto the GameObject.
	Also immediately loads the model based on the name passed.
	\param sModelName A string ID referencing a model in ModelSingleton */
	void attachModel(std::string sModelName);

	/**
	Attaches a new instance of a CPCamera onto the GameObject. */
	void attachCamera();

	/**
	Attaches a new instance of a CPLightSource onto the GameObject. */
	void attachLight();

	// dettachcomponent (?)


	// All component functions

	// MODEL //

	/**
	Calls the rotate() function from CPModel.
	\sa CPModel::rotate(); */
	void rotateModel(float fAngle, float fX, float fY, float fZ);

	/**
	Calls the drawModel() function from CPModel.
	\sa CPModel::drawModel(); */
	void drawModel() const;

	/**
	Calls the drawModel() function from CPModel.
	\sa CPModel::drawModel(); */
	void drawModel(sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const;

	/**
	Calls the setAngle() function from CPModel.
	\sa CPModel::setAngle(); */
	void setModelAngle(float fXAngle, float fYAngle, float fZAngle);

	/**
	Calls the move() function from CPModel.
	\sa CPModel::move(); */
	void moveModel(float fIncrement);

	/**
	Calls the move() function from CPModel.
	\sa CPModel::move(); */
	void moveModel(float fXChange, float fYChange, float fZChange);

	/**
	Calls the setPosition() function from CPModel.
	\sa CPModel::setPosition(); */
	void setModelPosition(float fXPos, float fYPos, float fZPos);

	/**
	Calls the setColour() function from CPModel.
	\sa CPModel::setColour(); */
	void setModelColour(float fR, float fG, float fB);

	/**
	Calls the setCamLock() function from CPModel.
	\sa CPModel::setCamLock(); */
	void setModelCamLock(bool b);

	/**
	Calls the getCamLock() function from CPModel.
	\sa CPModel::getCamLock(); */
	bool getModelCamLock();

	/**
	Calls the update() function from CPModel.
	\sa CPModel::update(); */
	void updateModel(sf::RenderWindow& window);

	/**
	Calls the getPosition() function from CPModel.
	\sa CPModel::getPosition(); */
	sf::Vector3f getModelPosition();


	// CAMERA //

	/**
	Calls the getPosition() function from CPCamera.
	\sa CPCamera::getPosition(); */
	sf::Vector3f getCameraPosition();

	/**
	Calls the getAngle() function from CPCamera.
	\sa CPCamera::getAngle(); */
	sf::Vector3f getCameraAngle() const;

	/**
	Calls the setPosition() function from CPCamera.
	\sa CPCamera::setPosition(); */
	void setCameraPosition(sf::Vector3f vPosition);

	/**
	Calls the setPosition() function from CPCamera.
	\sa CPCamera::setPosition(); */
	void setCameraPosition(float fX, float fY, float fZ);

	/**
	Calls the move() function from CPCamera.
	\sa CPCamera::move(); */
	void moveCamera(float fX, float fY, float fZ);

	/**
	Calls the moveForward() function from CPCamera.
	\sa CPCamera::moveForward(); */
	void moveCameraForward(float fIncrement);

	/**
	Calls the strafeRight() function from CPCamera.
	\sa CPCamera::strafeRight(); */
	void strafeCameraRight(float fIncrement);

	/**
	Calls the setAngle() function from CPCamera.
	\sa CPCamera::setAngle(); */
	void setCameraAngle(sf::Vector3f vAngle);

	/**
	Calls the setAngle() function from CPCamera.
	\sa CPCamera::setAngle(); */
	void setCameraAngle(float fX, float fY, float fZ);

	/**
	Calls the rotate() function from CPCamera.
	\sa CPCamera::rotate(); */
	void rotateCamera(float fX, float fY, float fZ);


	// LIGHT //

	/**
	Calls the setPosition() function from CPLightSource.
	\sa CPLightSource::setPosition(); */
	void setLightPosition(sf::Vector3f vfPosition);

	/**
	Calls the setAmbient() function from CPLightSource.
	\sa CPLightSource::setAmbient(); */
	void setAmbient(sf::Vector3f vfAmbient);

	/**
	Calls the setDiffuse() function from CPLightSource.
	\sa CPLightSource::setDiffuse(); */
	void setDiffuse(sf::Vector3f vfDiffuse);

	/**
	Calls the setSpecular() function from CPLightSource.
	\sa CPLightSource::setSpecular(); */
	void setSpecular(sf::Vector3f vfSpecular);

	/**
	Calls the toggleLight() function from CPLightSource.
	\sa CPLightSource::toggleLight(); */
	void toggleLight();

	/**
	Calls the updateAll() function from CPLightSource.
	\sa CPLightSource::updateAll(); */
	void updateLightAll();

	/**
	Calls the updatePosition() function from CPLightSource.
	\sa CPLightSource::updatePosition(); */
	void updateLightPos(sf::Vector3f vCamAngle, sf::Vector3f vCamPos);
};

#endif // GAMEOBJECT_H