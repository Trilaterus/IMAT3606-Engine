/** \file CPControllable.h
The header file for the ComponentControllable class.
*/
#ifndef CPCONTROLLABLE_H
#define CPCONTROLLABLE_H

#include <SFML\Graphics.hpp>
#include <algorithm>
#include <set>

class CPControllable
{
private:
	std::set<sf::Event> m_Events; // Events to listen out for

public:
	CPControllable();

	bool handleEvent(sf::Event sfEvent); // returns true if the event passed is the same as one of the listeners
	void addMouseListener();
	void addKeyListener(sf::Keyboard::Key sfKey);
};

#endif