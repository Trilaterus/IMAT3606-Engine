/** \file CPLightSource.cpp
The ComponentLightSource class allows the GameObject that has it attached to emit
light. The lights colour, position and attentuation can be changed. To use a CPLightSource
in code you must remember to call updateAll() once to enable the light (although this is
usually done for you in the Scene class initialisation).
*/

#include "CPLightSource.h"

/**
The only constructor the the CPLightSource class.
*/
CPLightSource::CPLightSource()
{
	for (int i = 0; i < 7; i++)
	{
		if (!glIsEnabled(GL_LIGHT0 + i))
		{
			glEnable(GL_LIGHT0 + i);
			m_iGLLightID = GL_LIGHT0 + i;
			m_bIsLightOn = true;
			break;
		}
		else
		{
			// move through loop
		}
	}

	m_vfAmbient = sf::Vector3f(0.0f, 0.0f, 0.0f);
	m_vfDiffuse = sf::Vector3f(0.0f, 0.0f, 0.0f);
	m_vfSpecular = sf::Vector3f(0.0f, 0.0f, 0.0f);
	m_vfPosition = sf::Vector3f(0.0f, 0.0f, 0.0f);
}

/**
Replaces the current LightSource position with the 3D vector passed.

\param vfPosition The new lightsource position float vector.
*/
void CPLightSource::setPosition(sf::Vector3f vfPosition)
{
	m_vfPosition = vfPosition;
}

/**
Replaces the current RGB ambient light value with the 3D vector passed.

\param vfAmbient The new ambient colour vector on a scale from 0 to 1.
*/
void CPLightSource::setAmbient(sf::Vector3f vfAmbient)
{
	m_vfAmbient = vfAmbient;
}

/**
Replaces the current RGB diffuse light value with the 3D vector passed.

\param vfDiffuse The new diffuse colour vector on a scale from 0 to 1.
*/
void CPLightSource::setDiffuse(sf::Vector3f vfDiffuse)
{
	m_vfDiffuse = vfDiffuse;
}

/**
Replaces the current RGB specular light value with the 3D vector passed.

\param vfSpecular The new specular colour vector on a scale from 0 to 1.
*/
void CPLightSource::setSpecular(sf::Vector3f vfSpecular)
{
	m_vfSpecular = vfSpecular;
}

/**
Toggles the diffuse lighting on and off.
*/
void CPLightSource::toggleLight()
{
	if (m_bIsLightOn)
	{
		glDisable(m_iGLLightID);
		m_bIsLightOn = false;
	}
	else
	{
		glEnable(m_iGLLightID);
		m_bIsLightOn = true;
	}
}

/**
Binds the associated colour values to the appropriate OpenGL functions.
Call this function once to enable the lights, although it is usually done
through the Scene class.
*/
void CPLightSource::updateAll()
{
	GLfloat amb[] = { m_vfAmbient.x, m_vfAmbient.y, m_vfAmbient.z, 1.0f };
	GLfloat dif[] = { m_vfDiffuse.x, m_vfDiffuse.y, m_vfDiffuse.z, 1.0f };
	GLfloat spec[] = { m_vfSpecular.x, m_vfSpecular.y, m_vfSpecular.z, 1.0f };
	glLightfv(m_iGLLightID, GL_AMBIENT, amb);
	glLightfv(m_iGLLightID, GL_DIFFUSE, dif);
	glLightfv(m_iGLLightID, GL_SPECULAR, spec);

	GLfloat pos[] = { m_vfPosition.x, m_vfPosition.y, m_vfPosition.z, 1.0f };
	glLightfv(m_iGLLightID, GL_POSITION, pos);
}

/**
Updates the position of the light based on the camera.

\param vfCameraAngle A 3D vector representing the angle offsets of the camera.
\param vfCameraPos A 3D vector representing the position offsets of the camera.
*/
void CPLightSource::updatePosition(sf::Vector3f vfCameraAngle, sf::Vector3f vfCameraPos)
{
	glRotatef(vfCameraAngle.x, 1.f, 0.f, 0.f);
	glRotatef(vfCameraAngle.y, 0.f, 1.f, 0.f);
	glRotatef(vfCameraAngle.z, 0.f, 0.f, 1.f);
	glTranslatef(vfCameraPos.x, vfCameraPos.y, vfCameraPos.z);

	GLfloat pos[] = { m_vfPosition.x, m_vfPosition.y, m_vfPosition.z, 1.0f };

	glLightfv(m_iGLLightID, GL_POSITION, pos);
}