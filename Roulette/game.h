#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "UImodel.h"

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

	//Mouse positions
	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;

	//Stats rectangle shape set
	sf::Vector2f gridSize;
	//unsigned gridSizeU = static_cast<unsigned>(gridSizeF); 
	
	//Resources
	sf::Font font; 

	//Text 
	sf::Text uiText; 

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	sf::RectangleShape stats;
	sf::RectangleShape stats2;
	sf::RectangleShape stats3;
	sf::RectangleShape stats4;

	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;
	
	//Private functions 
	void initVar(); 
	void initWindow(); 
	void initFonts(); 
	void initText(); 
	void initEnemies(); 
	void initStats();
	void initStats2();
	void initStats3();
	void initStats4();

public:
	//Constructor and destructor 
	game(); 
	virtual ~game(); 

	//Accessors 
	const bool isRunning() const; 

	//Functions 
	void pollEvents(); 
	void updateMousePositions(); 
	void updateText();
	void updateEnemies(); 
	void update(); 

	void updateStats();
	
	void renderText(sf::RenderTarget &target); 
	void renderEnemies(); 
	void renderStats(); 
	void render();

	void colorChange();

};