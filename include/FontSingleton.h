/**
A singleton class which stores sf::Fonts in order to ensure efficiency
when drawing and creating text.

@author Hussain */

#ifndef FONTSINGLETON_H
#define FONTSINGLETON_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

class FontSingleton // This class is a singleton
{
private:
	FontSingleton();
	FontSingleton(FontSingleton& const);
	void operator=(FontSingleton& const);

	std::map<std::string, sf::Font> m_AllFonts; 

public:
	/**
	Returns the only instance of the FontSingleton.
	@return The only instance of FontSingleton */
	static FontSingleton& instance();

	/**
	Loads a font into the singleton and returns a bool
	determining its success. You may pass the ID of
	"defualt" to change the default font.
	@param sName The associated ID for the font
	@param sFileName The file path to the font file
	@return A boolean representing its success */
	bool loadFont(std::string sName, std::string sFileName); 

	/**
	Returns the font specified by a passed ID.
	@param sName The string ID of the font
	@return An sf::Font address related to the ID passed */
	sf::Font& getFont(std::string sName);
};

#endif