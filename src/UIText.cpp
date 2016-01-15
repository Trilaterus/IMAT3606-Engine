#include "UIText.h"

UIText::UIText(std::string sText, float fXPos, float fYPos)
{
	m_sText = sText;
	m_vPosition.x = fXPos;
	m_vPosition.y = fYPos;
	m_sfColour = sf::Color::Black;
}

sf::Rect<float> UIText::getBounds()
{
	sf::Text text;
	text.setFont(FontSingleton::instance().getFont("default"));
	text.setPosition(m_vPosition);
	text.setString(m_sText);
	return text.getGlobalBounds();
}

void UIText::setColour(sf::Color sfColour)
{
	m_sfColour = sfColour;
}

void UIText::setString(std::string sText)
{
	m_sText = sText;
}

void UIText::setPosition(sf::Vector2f vfPosition)
{
	m_vPosition = vfPosition;
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text text;
	text.setFont(FontSingleton::instance().getFont("default"));
	text.setPosition(m_vPosition);
	text.setString(m_sText);
	text.setColor(m_sfColour);
	target.draw(text);
}