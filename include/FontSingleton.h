/** \file FontSingleton.h
The header file for the FontSingleton class.
*/

#ifndef FONTSINGLETON_H
#define FONTSINGLETON_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

class FontSingleton // This class is a singleton
{
private:
	FontSingleton();
	FontSingleton(FontSingleton const&);
	void operator=(FontSingleton const&);

	std::map<std::string, sf::Font> m_AllFonts; 

public:
	static FontSingleton& instance(); // get instance of FontSingleton

	bool loadFont(std::string sName, std::string sFileName); // save font to singleton under a specified name
	sf::Font& getFont(std::string sName); // get font by map name
};

#endif