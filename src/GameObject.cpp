#include "GameObject.h"

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->~CPModel();
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// Model Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

void GameObject::attachModel()
{
	m_pCPModel = new CPModel();
}

void GameObject::attachModel(std::string sModelName)
{
	m_pCPModel = new CPModel(sModelName);
}

void GameObject::rotateModel(float fAngle, float fX, float fY, float fZ)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->rotate(fAngle, fX, fY, fZ);
	}
}

void GameObject::setModelAngle(float fXAngle, float fYAngle, float fZAngle)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setAngle(fXAngle, fYAngle, fZAngle);
	}
}

void GameObject::moveModel(float fIncrement)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->move(fIncrement);
	}
}

void GameObject::moveModel(float fXChange, float fYChange, float fZChange)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->move(fXChange, fYChange, fZChange);
	}
}

void GameObject::setModelPosition(float fXPos, float fYPos, float fZPos)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setPosition(fXPos, fYPos, fZPos);
	}
}

void GameObject::drawModel(sf::RenderWindow& window) const
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->drawModel(window);
	}
}

void GameObject::drawModel(sf::RenderWindow& window, sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->drawModel(window, vCamAngle, vCamPos);
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// Camera Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

void GameObject::attachCamera()
{
	m_pCPCamera = new CPCamera;
}

sf::Vector3f GameObject::getCameraPosition()
{
	if (m_pCPCamera != nullptr)
	{
		return m_pCPCamera->getPosition();
	}
}

sf::Vector3f GameObject::getCameraAngle() const
{
	if (m_pCPCamera != nullptr)
	{
		return m_pCPCamera->getAngle();
	}
}

void GameObject::setCameraPosition(sf::Vector3f vPosition)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setPosition(vPosition);
	}
}

void GameObject::setCameraPosition(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setPosition(fX, fY, fZ);
	}
}

void GameObject::moveCamera(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->move(fX, fY, fZ);
	}
}

void GameObject::moveCameraForward(float fIncrement)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->moveForward(fIncrement);
	}
}

void GameObject::strafeCameraRight(float fIncrement)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->strafeRight(fIncrement);
	}
}

void GameObject::setCameraAngle(sf::Vector3f vAngle)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setAngle(vAngle);
	}
}

void GameObject::setCameraAngle(float fX, float fY, float fZ)
{
	if (m_pCPCamera != nullptr)
	{
		m_pCPCamera->setAngle(fX, fY, fZ);
	}
}

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

void GameObject::attachLight()
{
	m_pCPLight = new CPLightSource;
}

void GameObject::setLightPosition(sf::Vector3f vfPosition)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setPosition(vfPosition);
	}
}

void GameObject::setAmbient(sf::Vector3f vfAmbient)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setAmbient(vfAmbient);
	}
}

void GameObject::setDiffuse(sf::Vector3f vfDiffuse)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setDiffuse(vfDiffuse);
	}
}

void GameObject::setSpecular(sf::Vector3f vfSpecular)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->setSpecular(vfSpecular);
	}
}

void GameObject::toggleLight()
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->toggleLight();
	}
}

void GameObject::updateLightAll()
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->updateAll();
	}
}

void GameObject::updateLightPos(sf::Vector3f vCamAngle, sf::Vector3f vCamPos)
{
	if (m_pCPLight != nullptr)
	{
		m_pCPLight->updatePosition(vCamAngle, vCamPos);
	}
}

// // // // // // // // // // // // // // // // // // // // // // // // // // //
// Duplicate Functions
// // // // // // // // // // // // // // // // // // // // // // // // // // //

void GameObject::update(sf::RenderWindow& window)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->update(window);
	}
}