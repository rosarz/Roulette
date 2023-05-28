#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

/*
	Class with the game engine
*/

class game
{
private: 
	//Variable
	sf::RenderWindow* window; 
	sf::VideoMode videoMode; 
	sf::Event eve; 

	//Private functions 
	void initVar(); 
	void initWindow(); 

public:
	//Constructor and destructor 
	game(); 
	virtual ~game(); 

	//Accessors 
	const bool isRunning() const; 

	//Functions 
	void pollEvents(); 
	void update(); 
	void render();

};