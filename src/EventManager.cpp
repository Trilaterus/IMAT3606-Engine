#include "EventManager.h"

EventManager::EventManager()
{

}

EventManager& EventManager::getInstance()
{
	static EventManager instance;
	return instance;
}

void EventManager::receiveEvent(int iKey)
{
	m_iCurrentEvent = iKey;
}

int EventManager::getEvent()
{
	int tmp = m_iCurrentEvent;
	if (tmp != -1)
	{
		int i = 0;
	}
	return tmp;
}

void EventManager::resetEvent()
{
	m_iCurrentEvent = -1;
}