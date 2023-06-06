#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class uiText
{
public:
	//Text object  
	sf::Text _text;
	sf::Font font;

	//Constructors 
	uiText(); 
	uiText(int size, sf::Color, std::string text, float x, float y);

	//Initialize font 
	void initFont();
};

