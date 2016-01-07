#ifndef CPMODEL_H
#define CPMODEL_H

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

class CPModel
{
private:
	sf::Clock clock;

public:
	CPModel();

	void draw(sf::RenderWindow& window) const;
};

#endif