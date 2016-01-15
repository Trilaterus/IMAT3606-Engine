#include "CPModel.h"

void CPModel::init()
{
	clock.restart();
	m_bIsRotating = false;
	m_vfColour = { 1.0f, 1.0f, 1.0f };
	m_bCamLock = false;
}

CPModel::CPModel()
{
	init();

	// Default option loads an OpenGL textured cube.
	// We could directly use a sf::Texture as an OpenGL texture (with its Bind() member function),
	// but here we want more control on it (generate mipmaps, ...) so we create a new one from an image
	m_iTexture = 0;
	{
		sf::Image image;
		if (!image.loadFromFile("resources/texture.jpg"))
		{
			// Error
		}
		glGenTextures(1, &m_iTexture);
		glBindTexture(GL_TEXTURE_2D, m_iTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	// Bind the texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_iTexture);
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

	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	//glRotatef(90, 0.f, 1.f, 0.f); here is where you could add camera transformations to apply it to all the models

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void CPModel::drawModel(sf::Vector3f vCamAngle, sf::Vector3f vCamPos) const
{
	GLfloat colour[] = { m_vfColour.x, m_vfColour.y, m_vfColour.z };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colour);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoordsFirst());
	glNormalPointer(GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexNormsFirst());

	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

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

	// Then normal object transformations
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
