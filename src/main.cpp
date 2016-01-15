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
	//window.setFramerateLimit(60);

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
	// Set up controllable camera
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Can disable cull face if some objs normals are wrong (usually cuz downloaded off internet)
	glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera
	GameObject myCamera;
	myCamera.attachCamera();
	float fCameraSensitivity = 90; // 180 is significant for half of a full rotation, this formula makes it so that if the mouse moves the distance of the window the camera will rotate a full 360 degrees
	sf::Vector2i vWindowCenter(window.getSize().x / 2, window.getSize().y / 2);
	sf::Mouse::setPosition(vWindowCenter, window);
	window.setMouseCursorVisible(false); // Hide the mouse cursor
	bool bCamLeft, bCamRight, bCamFore, bCamBack; // used to create smooth camera movement
	sf::Texture tCrosshair;
	tCrosshair.loadFromFile("resources/textures/aquaCrosshair.png");
	sf::Sprite myCrosshair;
	myCrosshair.setTexture(tCrosshair);
	myCrosshair.setPosition(vWindowCenter.x, vWindowCenter.y);
	bool bLocked = true;

	// Second camera
	GameObject mySecondCamera;
	mySecondCamera.attachCamera();
	mySecondCamera.rotateCamera(0, 0, 25);

	GameObject* myCurrentCamera = &myCamera;
	glEnable(GL_LIGHTING);
	Scene myScene("resources/xml/NightDeadForest.xml", myCurrentCamera, window);
	
	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.0f, 500.f);

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Enable lighting (Would be easy to encapsulate in a component.. I hope)
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	/*
	glEnable(GL_LIGHTING);

	GameObject myLight;
	sf::Vector3f vfLightPos(10, 10, -10);
	myLight.attachLight();
	myLight.setLightPosition(vfLightPos);
	myLight.setDiffuse(sf::Vector3f(1.0f, 1.0f, 1.0f));
	myLight.updateLightAll();


	// Disable normal and color vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	*/

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Load files into Singletons
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	ModelSingleton::instance().init();

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Create Game Objects and their components
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	/*
	GameObject myObject;
	myObject.attachModel("Monkey");
	myObject.setModelPosition(0, 0, -10);
	myObject.setModelColour(1, 0.7, 0.7);

	GameObject myPodium;
	myPodium.attachModel("Podium");
	myPodium.setModelPosition(0, -2, -10);
	myPodium.setModelColour(0.5, 0.5, 0.5);

	GameObject myFloor;
	myFloor.attachModel("Floor");
	myFloor.setModelPosition(0, -4.5, 0);
	myFloor.setModelColour(0.8, 0.9, 0.8);

	GameObject mySword;
	mySword.attachModel("Sword");
	mySword.setModelPosition(7, -3, -8);
	mySword.setModelAngle(80, 10, -20);
	mySword.setModelColour(0.862745, 0.0784314, 0.235294);
	bool bSpin = false;
	float fAngle = 0.0;
	float fSpeed = -15.0;

	GameObject myForest;
	myForest.attachModel("Forest");
	myForest.setModelPosition(0, -4, 0);
	myForest.setModelColour(0.54, 0.27, 0.07);

	const int iStarTotal = 100;
	GameObject myStars[iStarTotal];
	RandomResource rand;
	for (int i = 0; i < iStarTotal; i++)
	{
		myStars[i].attachModel("Ball");
		myStars[i].setModelColour(1, 1, 1);
		myStars[i].setModelPosition(rand.generateFloat(-250, 250), rand.generateFloat(100, 200), rand.generateFloat(-250, 250));
	}
	*/

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Create UI elements
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	/*
	UIText myText("Hello World!", 5, 5);
	myText.setColour(sf::Color::Blue);

	UIText myCamText("Cam Text", 5, 30);
	myCamText.setColour(sf::Color::Green); // tracks the X axis rotation (since added functionality to stop camera from going upside down, caps at 90 and -90)

	sf::Clock myClock;
	*/

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

			myScene.handleEvent(sfevent);
			/*
			// Change camera angle if mouse moves
			if (event.type == sf::Event::MouseMoved)
			{
				if (bLocked)
				{
					if (sf::Mouse::getPosition(window) != vWindowCenter)
					{
						float XDiff = sf::Mouse::getPosition(window).x - vWindowCenter.x;
						float YDiff = sf::Mouse::getPosition(window).y - vWindowCenter.y;
						float XAngle = (XDiff / vWindowCenter.x) * fCameraSensitivity;
						float YAngle = (YDiff / vWindowCenter.y) * fCameraSensitivity;
						myCurrentCamera->rotateCamera(YAngle, XAngle, 0.0f);
						sf::Mouse::setPosition(vWindowCenter, window);
					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				bCamLeft = true;
			else
				bCamLeft = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				bCamRight = true;
			else
				bCamRight = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				bCamFore = true;
			else
				bCamFore = false;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				bCamBack = true;
			else
				bCamBack = false;

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (myCurrentCamera == &myCamera)
					myCurrentCamera = &mySecondCamera;
				else
					myCurrentCamera = &myCamera;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				myLight.toggleLight();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (bLocked)
					bSpin = true;
				else
				{
					bLocked = true;
					window.setMouseCursorVisible(false);
				}
			}
			*/
		}

		window.clear();
		myScene.update();
		glClear(GL_DEPTH_BUFFER_BIT);
		myScene.draw();
		/*
		// Update objects here
		myFloor.updateModel(window);
		myObject.rotateModel(1.0f, 0.0f, 1.0f, 0.0f);
		myObject.updateModel(window);
		myText.setString(std::to_string((int)(1 / myClock.getElapsedTime().asSeconds())));
		myClock.restart();
		myCamText.setString(std::to_string((int)myCurrentCamera->getCameraAngle().y));
		if (bCamLeft)
			myCurrentCamera->strafeCameraRight(-0.2f);
		if (bCamRight)
			myCurrentCamera->strafeCameraRight(0.2f);
		if (bCamFore)
			myCurrentCamera->moveCameraForward(0.2f);
		if (bCamBack)
			myCurrentCamera->moveCameraForward(-0.2f);
		if (bSpin)
		{
			fAngle += fSpeed;
			if (fAngle < 360 &&
				fAngle > -360)
			{
				mySword.rotateModel(fSpeed, 1, 0, 0);
				mySword.updateModel(window);
			}
			else
			{
				bSpin = false;
				mySword.setModelAngle(80, 10, -20);
				mySword.updateModel(window);
				fAngle = 0.0;
			}
		}

		// To draw any SFML behind the OpenGL use window.pushGLStates() and .popGLStates() similar to
		// drawing things after the OpenGL rendering here
		window.clear();

		// Update lights first
		myLight.updateLightPos(myCurrentCamera->getCameraAngle(), myCurrentCamera->getCameraPosition());

		//This clears the colour and depth buffer.
		glClear(GL_DEPTH_BUFFER_BIT);

		// Draw OpenGL objects here
		myFloor.drawModel(myCurrentCamera->getCameraAngle(), myCurrentCamera->getCameraPosition());
		myPodium.drawModel(myCurrentCamera->getCameraAngle(), myCurrentCamera->getCameraPosition());
		myObject.drawModel(myCurrentCamera->getCameraAngle(), myCurrentCamera->getCameraPosition());
		myForest.drawModel(myCurrentCamera->getCameraAngle(), myCurrentCamera->getCameraPosition());
		for (int i = 0; i < iStarTotal; i++)
		{
			myStars[i].drawModel(myCurrentCamera->getCameraAngle(), myCurrentCamera->getCameraPosition());
		}
		// By not passing the camera offsets I can draw 3D objects that don't move when
		// the camera does, hence giving the effect of a UI or held object
		glClear(GL_DEPTH_BUFFER_BIT);
		mySword.drawModel();

		// Draw some text on top of our OpenGL object
		window.pushGLStates();
		window.draw(myText);
		window.draw(myCamText);
		if (bLocked)
			window.draw(myCrosshair);
		window.popGLStates();
		*/

		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}