/** TODO
The ComponentControllable class gives the GameObject the ability to function
based on hardware events.

@author Hussain */

#ifndef CPCONTROLLABLE_H
#define CPCONTROLLABLE_H

#include <SFML\Graphics.hpp>
#include <algorithm>
#include <set>

class CPControllable
{
private:
	std::set<sf::Event> m_Events;

public:
	CPControllable();

	bool handleEvent(sf::Event sfEvent);
	void addMouseListener();
	void addKeyListener(sf::Keyboard::Key sfKey);
};

#endif