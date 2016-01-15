/** \file GameObject.cpp
The GameObject class allows components to be attached to it in
order to create a data driven system.
*/

#include "GameObject.h"

/**
The only constructor for the GameObject class
*/
GameObject::GameObject()
{
	
}

/**
The destructor for the GameObject class.
It calls the destructors of the attached components.
*/
GameObject::~GameObject()
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->~CPModel();
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// GameObject Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

/**
Checks whether the GameObject has a CPModel attached.

\return True if a CPModel is attached.
*/
bool GameObject::hasModel()
{
	if (m_pCPModel != nullptr)
		return true;
	else
		return false;
}

/**
Checks whether the GameObject has a CPCamera attached.

\return True if a CPCamera is attached.
*/
bool GameObject::hasCamera()
{
	if (m_pCPCamera != nullptr)
		return true;
	else
		return false;
}

/**
Checks whether the GameObject has a CPLightSource attached.

\return True if a CPLightSource is attached.
*/
bool GameObject::hasLight()
{
	if (m_pCPLight != nullptr)
		return true;
	else
		return false;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// Model Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

/**
Attaches a new instance of a CPModel onto the GameObject.
*/
void GameObject::attachModel()
{
	m_pCPModel = new CPModel();
}

/**
Attaches a new instance of a CPModel onto the GameObject.
Also immediately loads the model based on the name passed.

\param sModelName A string ID referencing a model in ModelSingleton.
*/
void GameObject::attachModel(std::string sModelName)
{
	m_pCPModel = new CPModel(sModelName);
}

/**
Calls the rotate() function from CPModel.

\sa CPModel::rotate();
*/
void GameObject::rotateModel(float fAngle, float fX, float fY, float fZ)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->rotate(fAngle, fX, fY, fZ);
	}
}

/**
Calls the setAngle() function from CPModel.

\sa CPModel::setAngle();
*/
void GameObject::setModelAngle(float fXAngle, float fYAngle, float fZAngle)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setAngle(fXAngle, fYAngle, fZAngle);
	}
}

/**
Calls the move() function from CPModel.

\sa CPModel::move();
*/
void GameObject::moveModel(float fIncrement)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->move(fIncrement);
	}
}

/**
Calls the move() function from CPModel.

\sa CPModel::move();
*/
void GameObject::moveModel(float fXChange, float fYChange, float fZChange)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->move(fXChange, fYChange, fZChange);
	}
}

/**
Calls the setPosition() function from CPModel.

\sa CPModel::setPosition();
*/
void GameObject::setModelPosition(float fXPos, float fYPos, float fZPos)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setPosition(fXPos, fYPos, fZPos);
	}
}

/**
Calls the drawModel() function from CPModel.

\sa CPModel::drawModel();
*/
void GameObject::drawModel() const
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->drawModel();
	}
}

/**
Calls the drawModel() function from CPModel.

\sa CPModel::drawModel();
*/
void GameObject::drawModel(sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->drawModel(vCamAngle, vCamPos);
	}
}

/**
Calls the setColour() function from CPModel.

\sa CPModel::setColour();
*/
void GameObject::setModelColour(float fR, float fG, float fB)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setColour(fR, fG, fB);
	}
}

/**
Calls the setCamLock() function from CPModel.

\sa CPModel::setCamLock();
*/
void GameObject::setModelCamLock(bool b)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setCamLock(b);
	}
}

/**
Calls the getCamLock() function from CPModel.

\sa CPModel::getCamLock();
*/
bool GameObject::getModelCamLock()
{
	if (m_pCPModel != nullptr)
	{
		return m_pCPModel->getCamLock();
	}
	else
	{
		std::cout << "GameObject: No Model attached!" << std::endl;
		return false;
	}
}

/**
Calls the update() function from CPModel.

\sa CPModel::update();
*/
void GameObject::updateModel(sf::RenderWindow& window)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->update(window);
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// Camera Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

/**
Attaches a new instance of a CPCamera onto the GameObject.
*/
void GameObject::attachCamera()
{
	m_pCPCamera = new CPCamera;
}

/**
Calls the getPosition() function from CPCamera.

\sa CPCamera::getPosition();
*/
sf::Vector3f GameObject::getCameraPosition()
{
	if (m_pCPCamera != nullptr)
	{
		return m_pCPCamera->getPosition();
	}
}

/**
Calls the getAngle() function from CPCamera.

\sa CPCamera::getAngle();
*/
sf::Vector3f GameObject::getCameraAngle() const
{
	if (m_pCPCamera != nullptr)
	{
		return m_pCPCamera->getAngle();
	}
}

/**
Calls the setPosition() function from CPCamera.

\sa CPCamera::setPosition();
*/
void GameObject::setCameraPosition(sf::Vector3f vPosition)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setPosition(vPosition);
	}
}

/**
Calls the setPosition() function from CPCamera.

\sa CPCamera::setPosition();
*/
void GameObject::setCameraPosition(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setPosition(fX, fY, fZ);
	}
}

/**
Calls the move() function from CPCamera.

\sa CPCamera::move();
*/
void GameObject::moveCamera(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->move(fX, fY, fZ);
	}
}

/**
Calls the moveForward() function from CPCamera.

\sa CPCamera::moveForward();
*/
void GameObject::moveCameraForward(float fIncrement)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->moveForward(fIncrement);
	}
}

/**
Calls the strafeRight() function from CPCamera.

\sa CPCamera::strafeRight();
*/
void GameObject::strafeCameraRight(float fIncrement)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->strafeRight(fIncrement);
	}
}

/**
Calls the setAngle() function from CPCamera.

\sa CPCamera::setAngle();
*/
void GameObject::setCameraAngle(sf::Vector3f vAngle)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setAngle(vAngle);
	}
}

/**
Calls the setAngle() function from CPCamera.

\sa CPCamera::setAngle();
*/
void GameObject::setCameraAngle(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setAngle(fX, fY, fZ);
	}
}

/**
Calls the rotate() function from CPCamera.

\sa CPCamera::rotate();
*/
void GameObject::rotateCamera(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->rotate(fX, fY, fZ);
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// LightSource Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

/**
Attaches a new instance of a CPLightSource onto the GameObject.
*/
void GameObject::attachLight()
{
	m_pCPLight = new CPLightSource;
}

/**
Calls the setPosition() function from CPLightSource.

\sa CPLightSource::setPosition();
*/
void GameObject::setLightPosition(sf::Vector3f vfPosition)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setPosition(vfPosition);
	}
}

/**
Calls the setAmbient() function from CPLightSource.

\sa CPLightSource::setAmbient();
*/
void GameObject::setAmbient(sf::Vector3f vfAmbient)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setAmbient(vfAmbient);
	}
}

/**
Calls the setDiffuse() function from CPLightSource.

\sa CPLightSource::setDiffuse();
*/
void GameObject::setDiffuse(sf::Vector3f vfDiffuse)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setDiffuse(vfDiffuse);
	}
}

/**
Calls the setSpecular() function from CPLightSource.

\sa CPLightSource::setSpecular();
*/
void GameObject::setSpecular(sf::Vector3f vfSpecular)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setSpecular(vfSpecular);
	}
}

/**
Calls the toggleLight() function from CPLightSource.

\sa CPLightSource::toggleLight();
*/
void GameObject::toggleLight()
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->toggleLight();
	}
}

/**
Calls the updateAll() function from CPLightSource.

\sa CPLightSource::updateAll();
*/
void GameObject::updateLightAll()
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->updateAll();
	}
}

/**
Calls the updatePosition() function from CPLightSource.

\sa CPLightSource::updatePosition();
*/
void GameObject::updateLightPos(sf::Vector3f vCamAngle, sf::Vector3f vCamPos)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->updatePosition(vCamAngle, vCamPos);
	}
}