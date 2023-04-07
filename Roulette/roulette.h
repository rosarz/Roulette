#pragma once
#include <SFML/Graphics.hpp>

class roulette
{
public: 
	sf::Vector2f pos;
	sf::Texture texture; 
	sf::Sprite sprite; 

	bool isLoaded(); 
	bool isExit(); 

	roulette(std::string, float, float, bool, bool); 
	
	bool setTexture(std::string); 
private: 

};

