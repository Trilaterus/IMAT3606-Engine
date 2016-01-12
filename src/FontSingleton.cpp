#include "FontSingleton.h"

FontSingleton::FontSingleton()
{
	sf::Font font;
	font.loadFromFile("resources/fonts/Sansation.ttf");
	m_AllFonts["default"] = font;
}

FontSingleton& FontSingleton::instance()
{
	static FontSingleton instance;
	return instance;
}

// Do not call a font "default" unless you purposely want to overwrite the current default
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