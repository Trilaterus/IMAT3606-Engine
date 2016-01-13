#ifndef CPMODEL_H
#define CPMODEL_H

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "ModelSingleton.h"

class CPModel
{
private:
	sf::Clock clock;
	sf::Vector3f m_vfPosition;
	sf::Vector3f m_vfAngles;
	GLuint m_iTexture;
	bool m_bIsRotating;
	sf::Vector3f m_vfQuaternion;
	std::string m_sModelName;

	void init(); // Called in every constructor

public:
	CPModel();
	CPModel(std::string sModelName); // The string identifier in the map of ModelSingleton
	~CPModel();

	void rotate(float fAngle, float fX, float fY, float fZ); // Change the angle by the increment
	void setAngle(float fXAngle, float fYAngle, float fZAngle); // Set the angle regardless of its previous angle
	void move(float fIncrement); // change the position by the increment based on the direction its facing
	void move(float fXChange, float fYChange, float fZChange); // change the position based on the increments
	void setPosition(float fXPos, float fYPos, float fZPos); // Set the position regardless of the previous position

	void update(sf::RenderWindow& window);
	void drawModel(sf::RenderWindow& window) const; // this would draw it not based on camera (potentially useful for 3D UI (?!?! Must TEST!)
	void drawModel(sf::RenderWindow& window, sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const; // Draw objects relative to camera
};

#endif