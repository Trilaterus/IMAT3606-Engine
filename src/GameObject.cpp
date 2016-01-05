#include "GameObject.h"

GameObject::GameObject()
{
	
}

void GameObject::attachControllable()
{
	m_pCPControllable = new CPControllable();
}

int GameObject::onKeyPress()
{
	if (m_pCPControllable != nullptr)
	{
		return m_pCPControllable->onKeyPress();
	}
	else
	{
		std::cout << "No instance on Controllable" << std::endl << std::endl;
	}
	return -1;
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