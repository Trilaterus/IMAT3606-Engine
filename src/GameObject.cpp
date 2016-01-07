#include "GameObject.h"

GameObject::GameObject()
{
	
}

void GameObject::attachModel()
{
	m_pCPModel = new CPModel();
}

void GameObject::attachControllable()
{
	m_pCPControllable = new CPControllable();
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