#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "UImodel.h"
#include "uiText.h"
#include "player.h"

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
	std::vector<UImodel> botBars;
	bool mouseHeld = false; 

	//Mouse positions
	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;
	
	//Background loader 
	sf::Texture texture;
	sf::Sprite background;

	//Game objects
	UImodel botBar;
	UImodel botBar2;
	UImodel botBar3;
	UImodel botBar4;
	UImodel botBar5;
	UImodel botBar6;
	UImodel botBar7;
	UImodel botBar8;

	//Player object 
	player p1; 
	
	//Private functions 
	void initVar(); 
	void initWindow(); 
	void initBackground();
	void initBar();

public:
	//Constructor and destructor 
	game(); 
	virtual ~game(); 

	//Accessors 
	const bool isRunning() const; 
 
	//Text objects		//lokalnie w metodzie dzia³a
	uiText tekst1;
	uiText tekst2;
	uiText tekst3;
	uiText tekst4;

	sf::Font font;
	void initFont();

	sf::Text tekst;

	//Functions 
	void pollEvents(); 
	void updateMousePositions(); 
	void updateText();
	void updateStats(); 
	void update(); 

	//Renders
	void renderText(sf::RenderTarget& target);
	void renderBar(); 
	void renderBackground(); 
	void render();

	void colorChange();

};