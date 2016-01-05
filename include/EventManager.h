#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>

class EventManager // singleton class
{
private:
	EventManager();
	EventManager(EventManager const&);
	void operator=(EventManager const&);

	int m_iCurrentEvent;

public:
	static EventManager& getInstance();

	void receiveEvent(int iKey);
	int getEvent();
	void resetEvent();
};

#endif