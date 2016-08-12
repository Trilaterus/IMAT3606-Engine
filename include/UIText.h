/**
The UIText class encapsulates the sf::Font to be polymorphically
stored as a UIElement. The class allows for text colours, strings,
sizes and positions to be changed.

@author Hussain */

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
	/**
	The default constructor for the class.
	You must pass a string to display, an X axis position
	and a Y axis position.
	@param sText The text to be displayed
	@param fXPos The X position of the text
	@param fYPos The Y position of the text */
	UIText(std::string sText, float fXPos, float fYPos);

	/**
	Returns the global bounds of the sf::Text, useful
	for determining whether the mouse is hovered over
	the text.
	@return An sf::Rect<float> defining the global bounds of the object */
	sf::Rect<float> getBounds();

	/**
	Replaces the current RBG colour with the colour passed.
	It needs an sf::Color value which is comprised of an
	R, G and B on a scale from 0 to 255.
	@param sfColour A new colour for the text */
	void setColour(sf::Color sfColour);

	/**
	Replaces the current string of the text with the
	string passed.
	@param sText A new string for the text */
	void setString(std::string sText);

	/**
	Replaces the current position of the text with
	the vector passed.
	@param vfPosition A 2D float vector representing the new position of the text */
	void setPosition(sf::Vector2f vfPosition);

	/**
	The sf::Drawable inherited function allows the window
	to draw the text.
	@param target The surface drawing the text.
	@param states Additional information that may modify rendering */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif