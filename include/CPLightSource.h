#ifndef CPLIGHT_H
#define CPLIGHT_H

#include <SFML\OpenGL.hpp>
#include <SFML\System.hpp>

/* How lights work:

Initialise all the values of the light (e.g position, ambient, diffuse etc.)
Use updateAll() once outside of the game loop to get it started
You can use updateAll() inside the game loop if you are changing the colour and pos of the lights in your loop
Mostly use updatePos() alongside passing the camera to ensure the spotlight is in the 'same place' all the time

*/

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