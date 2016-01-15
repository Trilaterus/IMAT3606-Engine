/** \file UIText.cpp
The UIText class encapsulates the sf::Font to be polymorphically
stored as a UIElement. The class allows for text colours, strings,
sizes and positions to be changed.
*/
#include "UIText.h"

/**
The default constructor for the class.
You must pass a string to display, an X axis position
and a Y axis position.

\param sText The text to be displayed.
\param fXPos The X position of the text.
\param fYPos The Y position of the text.
*/
UIText::UIText(std::string sText, float fXPos, float fYPos)
{
	m_sText = sText;
	m_vPosition.x = fXPos;
	m_vPosition.y = fYPos;
	m_sfColour = sf::Color::Black;
}

/**
Returns the global bounds of the sf::Text, useful
for determining whether the mouse is hovered over
the text.

\return An sf::Rect<float> defining the global bounds of the object.
*/
sf::Rect<float> UIText::getBounds()
{
	sf::Text text;
	text.setFont(FontSingleton::instance().getFont("default"));
	text.setPosition(m_vPosition);
	text.setString(m_sText);
	return text.getGlobalBounds();
}

/**
Replaces the current RBG colour with the colour passed.
It needs an sf::Color value which is comprised of an
R, G and B on a scale from 0 to 255.

\param sfColour A new colour for the text.
*/
void UIText::setColour(sf::Color sfColour)
{
	m_sfColour = sfColour;
}

/** 
Replaces the current string of the text with the
string passed.

\param sText A new string for the text.
*/
void UIText::setString(std::string sText)
{
	m_sText = sText;
}

/**
Replaces the current position of the text with
the vector passed.

\param vfPosition A 2D float vector representing the new position of the text.
*/
void UIText::setPosition(sf::Vector2f vfPosition)
{
	m_vPosition = vfPosition;
}

/**
The sf::Drawable inherited function allows the window
to draw the text.

\param target The surface drawing the text.
\param states
*/
void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Text text;
	text.setFont(FontSingleton::instance().getFont("default"));
	text.setPosition(m_vPosition);
	text.setString(m_sText);
	text.setColor(m_sfColour);
	target.draw(text);
}