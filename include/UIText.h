#ifndef UITEXT_H
#define UITEXT_H

#include <SFML\Graphics.hpp>
#include "FontSingleton.h"

class UIText : public sf::Drawable
{
private:
	std::string m_sText;
	sf::Vector2f m_vPosition;
	sf::Color m_sfColour;

public:
	UIText(std::string sText, float fXPos, float fYPos);

	sf::Rect<float> getBounds();
	void setColour(sf::Color sfColour);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif