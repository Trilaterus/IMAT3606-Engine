#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "UIText.h"

int main()
{
	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	// Create a sprite for the background
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("resources/background.jpg"))
		return EXIT_FAILURE;
	sf::Sprite background(backgroundTexture);

	// Make the window the active target for OpenGL calls
	// Note: If using sf::Texture or sf::Shader with OpenGL,
	// be sure to call sf::Texture::getMaximumSize() and/or
	// sf::Shader::isAvailable() at least once before calling
	// setActive(), as those functions will cause a context switch
	window.setActive();

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);

	// Disable lighting
	glDisable(GL_LIGHTING);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

	// Disable normal and color vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// Create a clock for measuring the time elapsed
	sf::Clock clock;

	// // // // // // // // // // //
	// Create Game Objects and their components
	GameObject myObject;
	myObject.attachModel();

	// // // // // // // // // // //
	// Create UI elements
	UIText myText("Hello World!", 10, 10);
	myText.setColour(sf::Color::Blue);

	// Start game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			// Escape key: exit
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			// Adjust the viewport when the window is resized
			if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				myObject.rotateModel(10, 1.0, 0.0, 0.0);

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				myObject.rotateModel(0, 1.0, 1.0, 1.0);
		}

		// Update objects here

		// Draw the background
		window.pushGLStates();
		window.draw(background);
		//window.clear();
		window.popGLStates();

		// Draw OpenGL objects here
		myObject.update(window);
		myObject.draw(window);

		// Draw some text on top of our OpenGL object
		window.pushGLStates();
		window.draw(myText);
		window.popGLStates();

		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}