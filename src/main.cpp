#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "UIText.h"
#include "RandomResource.h"
#include "Scene.h"

int main()
{
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	sf::RenderWindow window(sf::VideoMode(800, 600), "TQFTWMS ", sf::Style::Default, contextSettings);

	// Load and display splash screen
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
	window.setActive(); // Sets this window active for OpenGL calls

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

	// Can disable GL_CULL_FACE as .objs downloaded from external sources may not always have correct normals
	glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera

	// Set up cameras
	GameObject myCamera;
	myCamera.attachCamera();
	window.setMouseCursorVisible(false);
	GameObject mySecondCamera;
	mySecondCamera.attachCamera();
	mySecondCamera.rotateCamera(0, 0, 25);
	GameObject* myCurrentCamera = &myCamera;

	// Initialise environment through Scene class
	Scene* myCurrentScene;
	Scene myScene("resources/xml/NightDeadForest.xml", myCurrentCamera, window);
	Scene myColScene("resources/xml/CollisionTestArena.xml", myCurrentCamera, window);
	myCurrentScene = &myColScene;

	// Initialise singletons
	ModelSingleton::instance().init();

	// Start game loop
	while (window.isOpen())
	{
		sf::Event sfevent;
		while (window.pollEvent(sfevent))
		{
			if (sfevent.type == sf::Event::Closed)
			{
				window.close();
			}

			if (sfevent.type == sf::Event::Resized)
			{
				glViewport(0, 0, sfevent.size.width, sfevent.size.height);
			}

			if ((sfevent.type == sf::Event::KeyPressed) && (sfevent.key.code == sf::Keyboard::Space))
			{
				if (myCurrentCamera == &myCamera)
				{
					myCurrentCamera = &mySecondCamera;
					myCurrentScene->changeCamera(myCurrentCamera);
				}
				else
				{
					myCurrentCamera = &myCamera;
					myCurrentScene->changeCamera(myCurrentCamera);
				}
			}

			// Any events that happen to the objects are handled within the Scene function
			myCurrentScene->handleEvent(sfevent);
		}

		// Clear window, leave params blank for black background
		window.clear();
		// Update the objects in the Scene and apply some realtime controls
		myCurrentScene->update();
		// Draw the Scene which included the 3D objects and the UI
		myCurrentScene->draw();
		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}