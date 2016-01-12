#include "UIText.h"

UIText::UIText(std::string sText, float fXPos, float fYPos)
{
	m_sText = sText;
	m_vPosition.x = fXPos;
	m_vPosition.y = fYPos;
	m_sfColour = sf::Color::Black;
}

void UIText::setColour(sf::Color sfColour)
{
	m_sfColour = sfColour;
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