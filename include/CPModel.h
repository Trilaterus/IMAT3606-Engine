#ifndef CPMODEL_H
#define CPMODEL_H

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

class CPModel
{
private:
	sf::Clock clock;
	sf::Vector3f m_vfPosition;
	sf::Vector3f m_vfAngles;
	GLuint m_iTexture;
	bool m_bIsRotating;
	sf::Vector3f m_vfQuaternion;

public:
	CPModel();
	~CPModel();

	void rotate(float fAngle, float fX, float fY, float fZ);

	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;
};

#endif