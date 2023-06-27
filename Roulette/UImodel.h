#pragma once

#include "SFML/Graphics.hpp"

class UImodel
{
private:
	
public:
	//Game objects
	sf::RectangleShape stats;

	//Constructors
	UImodel();
	UImodel(float posx, float posy, float sizex, float sizey);
};