/** \file CPLightSource.h
The header file for the ComponentLightSource class.
*/
#ifndef CPLIGHT_H
#define CPLIGHT_H

#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>

class CPLightSource
{
private:
	int m_iGLLightID;
	sf::Vector3f m_vfAmbient;
	sf::Vector3f m_vfDiffuse;
	sf::Vector3f m_vfSpecular;
	sf::Vector3f m_vfPosition;
	bool m_bIsLightOn;

public:
	CPLightSource();

	void setPosition(sf::Vector3f vfPosition);
	void setAmbient(sf::Vector3f vfAmbient);
	void setDiffuse(sf::Vector3f vfDiffuse);
	void setSpecular(sf::Vector3f vfSpecular);

	void toggleLight();
	void updateAll(); // Only use in a loop if the light is changing colours a lot
	void updatePosition(sf::Vector3f vfCameraAngle, sf::Vector3f vfCameraPos);
};

#endif