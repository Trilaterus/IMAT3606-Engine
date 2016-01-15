/** \file CPCamera.h
The header file for the ComponentCamera class.
*/
#ifndef CPCAMERA_H
#define CPCAMERA_H

#include <SFML\Graphics.hpp>

class CPCamera
{
private:
	sf::Vector3f m_vPosition;
	sf::Vector3f m_vAngles;

public:
	CPCamera();

	sf::Vector3f getPosition();
	sf::Vector3f getAngle() const;

	void setPosition(sf::Vector3f vPosition);
	void setPosition(float fX, float fY, float fZ);
	void move(float fX, float fY, float fZ);
	void moveForward(float fIncrement); // Move in the direction currently facing (only on a 2D axis)
	void strafeRight(float fIncrement); // Move in the direction 90 degrees from where you are facing
	void setAngle(sf::Vector3f vAngle);
	void setAngle(float fX, float fY, float fZ);
	void rotate(float fX, float fY, float fZ);
};

#endif // CPCAMERA_H