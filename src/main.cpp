#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "UIText.h"
#include <GLM\glm.hpp>

int main()
{
	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

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

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Enable lighting (Would be easy to encapsulate in a component.. I hope)
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// Change light position
	GLfloat lightpos[] = { 10, 10, 10, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	// Changle light colour
	GLfloat colour1[] = { 1.f, 0.7f, 0.7f, 1.0f }; // example here and in draw area of how to add material colour to objects
	GLfloat colour2[] = { 0.7f, 0.7f, 1.0f, 1.0f };

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Set up controllable camera
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	sf::Vector2f cameraPos(0.0f, -3.0f);
	sf::Vector3f cameraAngle;

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

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Load files into Singletons
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	std::string sObjPath = "resources/objs/";
	ModelSingleton::instance().loadModel("Monkey", sObjPath + "monkey.obj");
	ModelSingleton::instance().loadModel("Floor", sObjPath + "plane.obj");

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Create Game Objects and their components
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	GameObject myObject;
	myObject.attachModel("Monkey");
	myObject.setPosition(0, 0, -3);

	GameObject myFloor;
	myFloor.attachModel("Floor");
	myFloor.setPosition(0, -10, -10);

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Create UI elements
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	UIText myText("Hello World!", 5, 5);
	myText.setColour(sf::Color::Blue);

	sf::Clock myClock;

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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				cameraPos.x += 1;

		}

		// Update objects here
		myFloor.update(window);
		myObject.rotateModel(1.0, 1, 0, 0);
		myObject.update(window);
		myText.setString(std::to_string((int)(1 / myClock.getElapsedTime().asSeconds())));
		myClock.restart();

		// Draw the background
		//window.pushGLStates();
		//window.draw(background);
		//window.popGLStates();
		window.clear();

		// Draw OpenGL objects here
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour1);
		myFloor.drawModel(window);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour2);
		myObject.drawModel(window);

		// Draw some text on top of our OpenGL object
		window.pushGLStates();
		window.draw(myText);
		window.popGLStates();

		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}