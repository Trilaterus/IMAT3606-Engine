/**
The Scene class uses an XML to define all the variables of the GameObject,
its components and currently some UIText. It requires a single camera and
a window to perform the necessary functions such as updating and drawing
all of its held GameObjects and UITexts.

@author Hussain */

#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include "UIText.h"
#include <array>
#include "RandomResource.h"
#include "TDCD.h"

class Scene
{
private:
	std::map<std::string, GameObject*> m_vGameObjects;
	std::map<std::string, UIText*> m_vUITexts;
	GameObject* m_pCamera;
	sf::RenderWindow* m_pWindow;
	bool m_bIsMouseLocked; // is the mouse locked
	sf::Clock m_Clock;
	GameObject m_aStars[100];
	sf::Texture m_TextureCrosshair;

public:
	/**
	The default constructor for the Scene class. It needs
	a file path to the XML holding information about the
	environment, a pointer to a GameObject that has a camera
	and a reference to the window to draw the SFML elements.
	\param sFileName The file path to the XML environment
	\param Camera A GameObject with a camera component attached
	\param Window A reference to an sf::RenderWindow */
	Scene(std::string sFileName, GameObject* Camera, sf::RenderWindow& Window);

	/**
	Changes the current camera with the GameObject camera passed.
	\param Camera The new camera to use for drawing and updating */
	void changeCamera(GameObject* Camera);

	/**
	Call within the pollEvent() function of SFML. It allows
	for the functions to be performed based on incoming
	hardware events.
	\param The currently polled sf::Event */
	void handleEvent(sf::Event sfEvent);

	/**
	Calls the update function on all the GameObjects and allows for
	functions to be bound to realtime events. */
	void update();

	/**
	Draws all of the objects in a specific order to ensure the
	Z ordering is realistic and so that SMFL and OpenGL can render
	together. */
	void draw();
};

#endif