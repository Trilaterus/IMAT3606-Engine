#include "UIText.h"

UIText::UIText(std::string sText, float fXPos, float fYPos)
{
	m_sText = sText;
	m_vPosition.x = fXPos;
	m_vPosition.y = fYPos;
}

void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text text;
	text.setFont(FontSingleton::instance().getFont("default"));
	text.setPosition(m_vPosition);
	text.setString(m_sText);
	target.draw(text);
}