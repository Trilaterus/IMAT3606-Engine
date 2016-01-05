#include "CPControllable.h"

CPControllable::CPControllable()
{

}

//void CPControllable::setKeyListener(int iKey)
//{
//	m_viKeys.push_back(iKey);
//}

int CPControllable::onKeyPress()
{
	return EventManager::getInstance().getEvent();
}