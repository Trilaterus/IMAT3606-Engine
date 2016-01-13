#include "CPCamera.h"

CPCamera::CPCamera()
{
	
}

sf::Vector3f CPCamera::getPosition()
{
	return m_vPosition;
}

sf::Vector3f CPCamera::getAngle() const
{
	return m_vAngles;
}

void CPCamera::setPosition(sf::Vector3f vPosition)
{
	m_vPosition = vPosition;
}

void CPCamera::setPosition(float fX, float fY, float fZ)
{
	m_vPosition = { fX, fY, fZ };
}

void CPCamera::move(float fX, float fY, float fZ)
{
	m_vPosition.x += fX;
	m_vPosition.y += fY;
	m_vPosition.z += fZ;

	/*	
	float newspeed = fSpeed * -1;
	float angle = (rotationAngle * 3.14) / 180;
	m_fZPos += newspeed * cos(angle);
	m_fXPos += newspeed * sin(angle);
	*/
}

void CPCamera::moveForward(float fIncrement)
{
	float fAngle = (m_vAngles.y * 3.14) / 180; // convert y axis (which is left and right looking) angle to radians

	m_vPosition.x -= fIncrement * sin(fAngle);
	m_vPosition.z += fIncrement * cos(fAngle);
}

void CPCamera::strafeRight(float fIncrement)
{
	float fOffset;
	float fAngle;
	if (fIncrement < 0)
	{
		fOffset = -90;

		fAngle = ((m_vAngles.y + fOffset) * 3.14) / 180; // convert y axis (which is left and right looking) angle to radians

		m_vPosition.x -= -fIncrement * sin(fAngle);
		m_vPosition.z += -fIncrement * cos(fAngle);
	}
	else
	{
		fOffset = 90;

		fAngle = ((m_vAngles.y + fOffset) * 3.14) / 180; // convert y axis (which is left and right looking) angle to radians

		m_vPosition.x -= fIncrement * sin(fAngle);
		m_vPosition.z += fIncrement * cos(fAngle);
	}
	/*
	if (key == GLFW_KEY_A)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (key == GLFW_KEY_D)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	*/
}

void CPCamera::setAngle(sf::Vector3f vAngle)
{
	m_vAngles = vAngle;
}

void CPCamera::setAngle(float fX, float fY, float fZ)
{
	m_vAngles = { fX, fY, fZ };
}

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