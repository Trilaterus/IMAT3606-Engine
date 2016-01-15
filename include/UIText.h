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
	void setString(std::string sText);
	void setPosition(sf::Vector2f vfPosition);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif