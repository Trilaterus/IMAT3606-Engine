#include "CPModel.h"

void CPModel::init()
{
	clock.restart();
	m_bIsRotating = false;
	m_vfColour = { 1.0f, 1.0f, 1.0f };
	m_bCamLock = false;
	m_sModelName = "default";
}

CPModel::CPModel()
{
	init();
}

CPModel::CPModel(std::string sModelName)
{
	init();

	m_sModelName = sModelName;
}

CPModel::~CPModel()
{

}

void CPModel::rotate(float fAngle, float fX, float fY, float fZ)
{
	m_vfQuaternion.x = fAngle * fX;
	m_vfQuaternion.y = fAngle * fY;
	m_vfQuaternion.z = fAngle * fZ;
}

void CPModel::setAngle(float fXAngle, float fYAngle, float fZAngle)
{
	m_vfAngles.x = fXAngle;
	m_vfAngles.y = fYAngle;
	m_vfAngles.z = fZAngle;
}

void CPModel::move(float fIncrement)
{
	float fRadianAngle = (m_vfAngles.x * 3.14) / 180;
	m_vfPosition.z += fIncrement * cos(fRadianAngle);
	m_vfPosition.x += fIncrement * sin(fRadianAngle);
}

void CPModel::move(float fXChange, float fYChange, float fZChange)
{
	m_vfPosition.x += fXChange;
	m_vfPosition.y += fYChange;
	m_vfPosition.z += fZChange;
}

void CPModel::setPosition(float fXPos, float fYPos, float fZPos)
{
	m_vfPosition.x = fXPos;
	m_vfPosition.y = fYPos;
	m_vfPosition.z = fZPos;
}

void CPModel::setColour(float R, float G, float B)
{
	m_vfColour = { R, G, B };
}

void CPModel::setCamLock(bool b)
{
	m_bCamLock = b;
}

bool CPModel::getCamLock()
{
	return m_bCamLock;
}

sf::Vector3f CPModel::getPosition()
{
	return m_vfPosition;
}


void CPModel::update(sf::RenderWindow& window)
{
	m_vfAngles += m_vfQuaternion;
}

void CPModel::drawModel() const
{
	GLfloat colour[] = { m_vfColour.x, m_vfColour.y, m_vfColour.z };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoordsFirst());
	glNormalPointer(GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexNormsFirst());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
}

void CPModel::drawModel(sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const
{
	GLfloat colour[] = { m_vfColour.x, m_vfColour.y, m_vfColour.z };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoordsFirst());
	glNormalPointer(GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexNormsFirst());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (!m_bCamLock)
	{
		// Camera transformations happen first
		glRotatef(vCamAngle.x, 1.f, 0.f, 0.f);
		glRotatef(vCamAngle.y, 0.f, 1.f, 0.f);
		glRotatef(vCamAngle.z, 0.f, 0.f, 1.f);
		glTranslatef(vCamPos.x, vCamPos.y, vCamPos.z);
	}
	else
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	// Then normal object transformations
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
}