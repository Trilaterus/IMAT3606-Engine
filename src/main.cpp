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
	window.setFramerateLimit(60);

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
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	GameObject myLight;
	sf::Vector3f vfLightPos(0, 2, -8);
	myLight.attachLight();
	myLight.setLightPosition(vfLightPos);
	myLight.setDiffuse(sf::Vector3f(1.0f, 1.0f, 1.0f));
	myLight.updateLightAll();
	// Also attach ball model to light to see where it is
	myLight.attachModel("SmallBall");
	myLight.setModelPosition(vfLightPos.x, vfLightPos.y, vfLightPos.z);

	// Set some colours for object materials (will be changed to be added to CPModel)
	GLfloat colour[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // No colour
	GLfloat colour1[] = { 1.f, 0.7f, 0.7f, 1.0f }; // Light red
	GLfloat colour2[] = { 0.7f, 0.7f, 1.0f, 1.0f }; // Light blue

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.0f, 500.f);

	// Disable normal and color vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// Create a clock for measuring the time elapsed
	sf::Clock clock;

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Set up controllable camera
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Cull face disabled as objs downloaded from external sources have not got proper normals
	//glEnable(GL_CULL_FACE); // Cull triangles which normal is not towards the camera
	GameObject myCamera;
	myCamera.attachCamera();
	float fCameraSensitivity = 90; // 180 is significant for half of a full rotation, this formula makes it so that if the mouse moves the distance of the window the camera will rotate a full 360 degrees
	sf::Vector2i vWindowCenter(window.getSize().x / 2, window.getSize().y / 2);
	sf::Mouse::setPosition(vWindowCenter, window);
	window.setMouseCursorVisible(false); // Hide the mouse cursor
	UIText myCamText("Cam Text", 5, 30);
	myCamText.setColour(sf::Color::Green); // tracks the X axis rotation (since added functionality to stop camera from going upside down, caps at 90 and -90)
	bool bCamLeft, bCamRight, bCamFore, bCamBack; // used to create smooth camera movement
	sf::Texture tCrosshair;
	tCrosshair.loadFromFile("resources/textures/aquaCrosshair.png");
	sf::Sprite myCrosshair;
	myCrosshair.setTexture(tCrosshair);
	myCrosshair.setPosition(vWindowCenter.x, vWindowCenter.y);

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Load files into Singletons
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	ModelSingleton::instance().init();

	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	// Create Game Objects and their components
	// // // // // // // // // // // // // // // // // // // // // // // // // // //
	GameObject myObject;
	myObject.attachModel("Monkey");
	myObject.setModelPosition(0, 0, -8);

	GameObject myFloor;
	myFloor.attachModel("Floor");
	myFloor.setModelPosition(0, -10, -15);

	GameObject mySword;
	mySword.attachModel("Sword");
	mySword.setModelPosition(7, -3, -8);
	mySword.setModelAngle(80, 10, -20);

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

			// Change camera angle if mouse moves
			if (event.type == sf::Event::MouseMoved)
			{
				if (sf::Mouse::getPosition(window) != vWindowCenter)
				{
					float XDiff = sf::Mouse::getPosition(window).x - vWindowCenter.x;
					float YDiff = sf::Mouse::getPosition(window).y - vWindowCenter.y;
					float XAngle = (XDiff / vWindowCenter.x) * fCameraSensitivity;
					float YAngle = (YDiff / vWindowCenter.y) * fCameraSensitivity;
					myCamera.rotateCamera(YAngle, XAngle, 0.0f); 
					sf::Mouse::setPosition(vWindowCenter, window);
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				myLight.toggleLight();
		}

		// Update objects here
		myFloor.update(window);
		myObject.rotateModel(1.0f, 0.0f, 1.0f, 0.0f);
		myObject.update(window);
		myText.setString(std::to_string((int)(1 / myClock.getElapsedTime().asSeconds())));
		myClock.restart();
		myCamText.setString(std::to_string((int)myCamera.getCameraAngle().y));
		if (bCamLeft)
			myCamera.strafeCameraRight(-0.2f);
		if (bCamRight)
			myCamera.strafeCameraRight(0.2f);
		if (bCamFore)
			myCamera.moveCameraForward(0.2f);
		if (bCamBack)
			myCamera.moveCameraForward(-0.2f);

		// To draw any SFML behind the OpenGL use window.pushGLStates() and .popGLStates() similar to
		// drawing things after the OpenGL rendering here
		window.clear();

		// Update lights first
		myLight.updateLightPos(myCamera.getCameraAngle(), myCamera.getCameraPosition());
		myLight.drawModel(window, myCamera.getCameraAngle(), myCamera.getCameraPosition());

		// Draw OpenGL objects here
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour1);
		myFloor.drawModel(window, myCamera.getCameraAngle(), myCamera.getCameraPosition());
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour2);
		myObject.drawModel(window, myCamera.getCameraAngle(), myCamera.getCameraPosition());
		// By not passing the camera offsets I can draw 3D objects that don't move when
		// the camera does, hence giving the effect of a UI or held object
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour);
		mySword.drawModel(window);

		// Draw some text on top of our OpenGL object
		window.pushGLStates();
		window.draw(myText);
		window.draw(myCamText);
		window.draw(myCrosshair);
		window.popGLStates();

		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}