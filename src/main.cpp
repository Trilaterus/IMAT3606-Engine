#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "UIText.h"
#include "RandomResource.h"
#include "Scene.h"

int main()
{
	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TQFTWMS ", sf::Style::Default, contextSettings);
	
	sf::Texture myTexture;
	if (!myTexture.loadFromFile("resources/textures/splash.png"))
	{
		return 0;
	}
	sf::Sprite mySplashScreen;
	mySplashScreen.setTexture(myTexture);
	window.pushGLStates();
	window.draw(mySplashScreen);
	window.popGLStates();
	window.display();
	
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// Sets this window active for OpenGL calls
	window.setActive();

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Set up OpenGL
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glEnable(GL_LIGHTING);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.0f, 500.f);

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Set up controllable cameras
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Can disable GL_CULL_FACE as .objs downloaded from external sources may not always have correct normals
	glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera
	GameObject myCamera;
	myCamera.attachCamera();
	window.setMouseCursorVisible(false); // Hide the mouse cursor
	
	// Second camera
	GameObject mySecondCamera;
	mySecondCamera.attachCamera();
	mySecondCamera.rotateCamera(0, 0, 25);

	GameObject* myCurrentCamera = &myCamera;

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Initialise objects through Scene class
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	Scene myScene("resources/xml/NightDeadForest.xml", myCurrentCamera, window);

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Initialise files into Singletons
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	ModelSingleton::instance().init();

	// Start game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event sfevent;
		while (window.pollEvent(sfevent))
		{
			// Close window: exit
			if (sfevent.type == sf::Event::Closed)
				window.close();

			// Adjust the viewport when the window is resized
			if (sfevent.type == sf::Event::Resized)
				glViewport(0, 0, sfevent.size.width, sfevent.size.height);

			if ((sfevent.type == sf::Event::KeyPressed) && (sfevent.key.code == sf::Keyboard::Space))
			{
				if (myCurrentCamera == &myCamera)
				{
					myCurrentCamera = &mySecondCamera;
					myScene.changeCamera(myCurrentCamera);
				}
				else
				{
					myCurrentCamera = &myCamera;
					myScene.changeCamera(myCurrentCamera);
				}
			}

			// Any events that happen to the objects are handled within the Scene function
			myScene.handleEvent(sfevent);
		}

		// Clear window, leave params blank for black background
		window.clear();
		// Update the objects in the Scene and apply some realtime controls
		myScene.update();
		// Draw the Scene which included the 3D objects and the UI
		myScene.draw();
		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}