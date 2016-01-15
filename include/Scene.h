#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"
#include "UIText.h"

class Scene
{
private:
	std::map<std::string, GameObject*> m_vGameObjects;
	std::map<std::string, UIText*> m_vUITexts;
	GameObject* m_pCamera;
	sf::RenderWindow* m_pWindow;
	bool m_bIsMouseLocked; // is the mouse locked

public:
	Scene(std::string sFileName, GameObject* Camera, sf::RenderWindow& Window); // Can only construct from valid XML file and by having some form of camera

	void update(sf::Event sfEvent);
	void draw();
};

#endif