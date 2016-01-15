/** \file CPCamera.cpp
The ComponentCamera class essentially stores a 3D position and angle vector in order to equally
offset all the object affected. Consider OpenGL to be a fixed window frame, to give the illusion
of moving a camera we move all the objects by an offset instead. This camera aims to provide a
First Person Shooter (or FPS) style camera.
*/

#include "CPCamera.h"

/**
The only constructor for the CPCamera class.
*/
CPCamera::CPCamera()
{
	
}

/**
Returns the current position of the camera as a 3D vector.

\return Current position as 3D vector.
*/
sf::Vector3f CPCamera::getPosition()
{
	return m_vPosition;
}

/**
Returns the current angle of the camera as a 3D vector.

\return Current angle as 3D vector.
*/
sf::Vector3f CPCamera::getAngle() const
{
	return m_vAngles;
}

/**
Replaces the current camera position vector with the vector passed.

\param vPosition The new camera position vector.
*/
void CPCamera::setPosition(sf::Vector3f vPosition)
{
	m_vPosition = vPosition;
}

/**
Replaces the current camera position vector with the 3 floats passed.

\param fX The new camera X axis position
\param fY The new camera Y axis position
\param fZ The new camera Z axis position
*/
void CPCamera::setPosition(float fX, float fY, float fZ)
{
	m_vPosition = { fX, fY, fZ };
}

/**
Moves the camera based on the 3 floats passed.

\param fX Moves the camera by the given amount on the X axis.
\param fY Moves the camera by the given amount on the Y axis.
\param fZ Moves the camera by the given amount on the Z axis.
*/
void CPCamera::move(float fX, float fY, float fZ)
{
	m_vPosition.x += fX;
	m_vPosition.y += fY;
	m_vPosition.z += fZ;
}

/**
Moves the camera forward based on the direction it is currently facing.
It can also be used to move backwards if a negative float is passed to it.

\param fIncrement The amount of distance to move.
*/
void CPCamera::moveForward(float fIncrement)
{
	float fAngle = (m_vAngles.y * 3.14) / 180; // convert y axis (which is left and right looking) angle to radians

	m_vPosition.x -= fIncrement * sin(fAngle);
	m_vPosition.z += fIncrement * cos(fAngle);
}

/**
Moves the camera to the right of the direction it is currently facing, similar to a strafe.
It can also be used to move left if a negative float is passed to it

\param fIncrement The amount of distance to strafe.
*/
void CPCamera::strafeRight(float fIncrement)
{
	float fOffset;
	float fAngle;
	if (fIncrement < 0)
	{
		fOffset = -90;

		fAngle = ((m_vAngles.y + fOffset) * 3.14) / 180;

		m_vPosition.x -= -fIncrement * sin(fAngle);
		m_vPosition.z += -fIncrement * cos(fAngle);
	}
	else
	{
		fOffset = 90;

		fAngle = ((m_vAngles.y + fOffset) * 3.14) / 180;

		m_vPosition.x -= fIncrement * sin(fAngle);
		m_vPosition.z += fIncrement * cos(fAngle);
	}
}

/**
Replaces the current angle of the camera with the 3D vector passed.

\param vAngle The new camera angle vector.
*/
void CPCamera::setAngle(sf::Vector3f vAngle)
{
	m_vAngles = vAngle;
}

/**
Replaces the current angle of the camera with the three floats passed.

\param fX The new X axis angle.
\param fY The new Y axis angle.
\param fZ The new Z axis angle.
*/
void CPCamera::setAngle(float fX, float fY, float fZ)
{
	m_vAngles = { fX, fY, fZ };
}

/**
Increments the current angle of the camera by the three floats passed.

\param fX The X axis angle increment.
\param fY The Y axis angle increment.
\param fZ The Z axis angle increment.
*/
void CPCamera::rotate(float fX, float fY, float fZ)
{
	m_vAngles.x += fX;
	if (m_vAngles.x > 90)
	{
		m_vAngles.x = 90;
	}
	else if (m_vAngles.x< -90)
	{
		m_vAngles.x = -90;
	}
	m_vAngles.y += fY;
	if (m_vAngles.y > 360)
	{
		m_vAngles.y = 0;
	}
	else if (m_vAngles.y < -360)
	{
		m_vAngles.y = 0;
	}
	m_vAngles.z += fZ;
}