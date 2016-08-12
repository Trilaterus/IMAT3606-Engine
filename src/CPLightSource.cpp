#include "CPLightSource.h"

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

void CPLightSource::setPosition(sf::Vector3f vfPosition)
{
	m_vfPosition = vfPosition;
}

void CPLightSource::setAmbient(sf::Vector3f vfAmbient)
{
	m_vfAmbient = vfAmbient;
}

void CPLightSource::setDiffuse(sf::Vector3f vfDiffuse)
{
	m_vfDiffuse = vfDiffuse;
}

void CPLightSource::setSpecular(sf::Vector3f vfSpecular)
{
	m_vfSpecular = vfSpecular;
}

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

void CPLightSource::updatePosition(sf::Vector3f vfCameraAngle, sf::Vector3f vfCameraPos)
{
	glRotatef(vfCameraAngle.x, 1.f, 0.f, 0.f);
	glRotatef(vfCameraAngle.y, 0.f, 1.f, 0.f);
	glRotatef(vfCameraAngle.z, 0.f, 0.f, 1.f);
	glTranslatef(vfCameraPos.x, vfCameraPos.y, vfCameraPos.z);

	GLfloat pos[] = { m_vfPosition.x, m_vfPosition.y, m_vfPosition.z, 1.0f };

	glLightfv(m_iGLLightID, GL_POSITION, pos);
}