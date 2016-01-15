/** \file FontSingleton.cpp
A singleton class which stores sf::Fonts in order to ensure efficiency
when drawing and creating text.
*/

#include "FontSingleton.h"

/**
The private constructor for the FontSingleton.
It loads a default font.
*/
FontSingleton::FontSingleton()
{
	sf::Font font;
	font.loadFromFile("resources/fonts/Sansation.ttf");
	m_AllFonts["default"] = font;
}

/**
Returns the only instance of the FontSingleton.

\return The only instance of FontSingleton.
*/
FontSingleton& FontSingleton::instance()
{
	static FontSingleton instance;
	return instance;
}

/**
Loads a font into the singleton and returns a bool
determining its success. You may pass the ID of
"defualt" to change the default font.

\param sName The associated ID for the font.
\param sFileName The file path to the font file.
\return A boolean representing its success.
*/
bool FontSingleton::loadFont(std::string sName, std::string sFileName)
{
	sf::Font font;
	if (!font.loadFromFile(sFileName))
	{
		std::cout << "FontSingleton: Error loading from - " << sFileName << std::endl;
		return false;
	}
	else
	{
		m_AllFonts[sName] = font;
		return true;
	}
}

/**
Returns the font specified by a passed ID.

\param sName The string ID of the font.
\return An sf::Font address related to the ID passed.
*/
sf::Font& FontSingleton::getFont(std::string sName)
{
	if (m_AllFonts.find(sName) == m_AllFonts.end())
	{
		// Not found
		return m_AllFonts["default"];
	}
	else
	{
		// Found
		return m_AllFonts[sName];
	}
}