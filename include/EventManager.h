#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>
#include <SFML\Graphics.hpp>

class EventManager // singleton class
{
private:
	EventManager();
	EventManager(EventManager const&);
	void operator=(EventManager const&);

public:
	static EventManager& getInstance();

	void passEvent(sf::Event sfEvent);
};

#endif