#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include "UIText.h"
#include <array>
#include "RandomResource.h"

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

public:
	Scene(std::string sFileName, GameObject* Camera, sf::RenderWindow& Window); // Can only construct from valid XML file and by having some form of camera

	void changeCamera(GameObject* Camera);

	void handleEvent(sf::Event sfEvent);
	void update();
	void draw();
};

#endif