#include "CPModel.h"

void CPModel::init()
{
	clock.restart();
	m_vfPosition.z = -3.f;
	m_vfAngles.y = 90;
	m_vfAngles.x = 180;
	m_bIsRotating = false;
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
	glDeleteTextures(1, &m_iTexture);
}

void CPModel::rotate(float fAngle, float fX, float fY, float fZ)
{
	m_vfQuaternion.x = fAngle * fX;
	m_vfQuaternion.y = fAngle * fY;
	m_vfQuaternion.z = fAngle * fZ;
}

void CPModel::update(sf::RenderWindow& window)
{
	// Update positon based on "mouse relative to screen" position
	m_vfPosition.x = sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
	m_vfPosition.y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;

	m_vfAngles += m_vfQuaternion;
}

void CPModel::draw(sf::RenderWindow& window) const
{
	// Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
	static const GLfloat cube[] =
	{
		// positions    // texture coordinates
		-20, -20, -20, 0, 0,
		-20, 20, -20, 1, 0,
		-20, -20, 20, 0, 1,
		-20, -20, 20, 0, 1,
		-20, 20, -20, 1, 0,
		-20, 20, 20, 1, 1,

		20, -20, -20, 0, 0,
		20, 20, -20, 1, 0,
		20, -20, 20, 0, 1,
		20, -20, 20, 0, 1,
		20, 20, -20, 1, 0,
		20, 20, 20, 1, 1,

		-20, -20, -20, 0, 0,
		20, -20, -20, 1, 0,
		-20, -20, 20, 0, 1,
		-20, -20, 20, 0, 1,
		20, -20, -20, 1, 0,
		20, -20, 20, 1, 1,

		-20, 20, -20, 0, 0,
		20, 20, -20, 1, 0,
		-20, 20, 20, 0, 1,
		-20, 20, 20, 0, 1,
		20, 20, -20, 1, 0,
		20, 20, 20, 1, 1,

		-20, -20, -20, 0, 0,
		20, -20, -20, 1, 0,
		-20, 20, -20, 0, 1,
		-20, 20, -20, 0, 1,
		20, -20, -20, 1, 0,
		20, 20, -20, 1, 1,

		-20, -20, 20, 0, 0,
		20, -20, 20, 1, 0,
		-20, 20, 20, 0, 1,
		-20, 20, 20, 0, 1,
		20, -20, 20, 1, 0,
		20, 20, 20, 1, 1
	};

	// Enable position and texture coordinates vertex components
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

	// Disable normal and color vertex components
	//glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	// Clear the depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CPModel::drawModel(sf::RenderWindow& window) const
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoordsFirst());
	glNormalPointer(GL_FLOAT, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexNormsFirst());

	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//This clears the colour and depth buffer.
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_vfPosition.x, m_vfPosition.y, m_vfPosition.z);
	glRotatef(m_vfAngles.x, 1.f, 0.f, 0.f);
	glRotatef(m_vfAngles.y, 0.f, 1.f, 0.f);
	glRotatef(m_vfAngles.z, 0.f, 0.f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, ModelSingleton::instance().getModel(m_sModelName).getVertexCoords().size() / 3);

	glDisableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}