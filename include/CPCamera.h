/**
The ComponentCamera class essentially stores a 3D position and angle vector in order to equally
offset all the objects affected. Consider OpenGL to be a fixed window frame, to give the illusion
of moving a camera we move all the objects by an offset instead. This camera aims to provide a
First Person Shooter (or FPS) style camera with strafe-like movement functions.

@author Hussain */

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

	/**
	Returns the current position of the camera as a 3D vector.
	@return Current position as 3D vector */
	sf::Vector3f getPosition();

	/**
	Returns the current angle of the camera as a 3D vector.
	@return Current angle as 3D vector */
	sf::Vector3f getAngle() const;

	/**
	Replaces the current camera position vector with the vector passed.
	@param vPosition The new camera position vector */
	void setPosition(sf::Vector3f vPosition);

	/**
	Replaces the current camera position vector with the 3 floats passed.
	@param fX The new camera X axis position
	@param fY The new camera Y axis position
	@param fZ The new camera Z axis position */
	void setPosition(float fX, float fY, float fZ);

	/**
	Moves the camera based on the 3 floats passed.
	@param fX Moves the camera by the given amount on the X axis
	@param fY Moves the camera by the given amount on the Y axis
	@param fZ Moves the camera by the given amount on the Z axis */
	void move(float fX, float fY, float fZ);

	/**
	Moves the camera forward based on the direction it is currently facing.
	It can also be used to move backwards if a negative float is passed to it.
	@param fIncrement The amount of distance to move */
	void moveForward(float fIncrement);

	/**
	Moves the camera to the right of the direction it is currently facing, similar to a strafe.
	It can also be used to move left if a negative float is passed to it
	@param fIncrement The amount of distance to strafe */
	void strafeRight(float fIncrement); // Move in the direction 90 degrees from where you are facing

	/**
	Replaces the current angle of the camera with the 3D vector passed.
	@param vAngle The new camera angle vector */
	void setAngle(sf::Vector3f vAngle);

	/**
	Replaces the current angle of the camera with the three floats passed.
	@param fX The new X axis angle
	@param fY The new Y axis angle
	@param fZ The new Z axis angle */
	void setAngle(float fX, float fY, float fZ);

	/**
	Increments the current angle of the camera by the three floats passed.
	@param fX The X axis angle increment
	@param fY The Y axis angle increment
	@param fZ The Z axis angle increment */
	void rotate(float fX, float fY, float fZ);
};

#endif // CPCAMERA_H