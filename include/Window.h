#ifndef WINDOW_H
#define WINDOW_H

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

class Window
{
private:
	sf::RenderWindow* m_sfWindow;

public:
	Window();
};

#endif // WINDOW_H