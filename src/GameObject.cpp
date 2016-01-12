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

void GameObject::attachModel()
{
	m_pCPModel = new CPModel();
}

void GameObject::attachModel(std::string sModelName)
{
	m_pCPModel = new CPModel(sModelName);
}

void GameObject::attachControllable()
{
	m_pCPControllable = new CPControllable();
}

void GameObject::rotateModel(float fAngle, float fX, float fY, float fZ)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->rotate(fAngle, fX, fY, fZ);
	}
}

void GameObject::setAngle(float fXAngle, float fYAngle, float fZAngle)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->setAngle(fXAngle, fYAngle, fZAngle);
	}
}

void GameObject::move(float fIncrement)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->move(fIncrement);
	}
}

void GameObject::move(float fXChange, float fYChange, float fZChange)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->move(fXChange, fYChange, fZChange);
	}
}

void GameObject::setPosition(float fXPos, float fYPos, float fZPos)
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

void GameObject::update(sf::RenderWindow& window)
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->update(window);
	}
}

void GameObject::draw(sf::RenderWindow& window) const
{
	if (m_pCPModel != nullptr)
	{
		m_pCPModel->draw(window);
	}
}

/* Example of function with handling for different components but same function name
void GameObject::setPosition(float fXPos, float fYPos)
{
	if (m_pComponentMovable != nullptr)
	{
		m_pComponentMovable->setPosition(fXPos, fYPos);
	}
	else
	{
		// Safely do nothing
	}
}
*/