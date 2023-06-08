#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <random>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "UImodel.h"
#include "uiText.h"
#include "player.h"

//	TODO
//	-  
//	- 

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
	std::vector<int> czerwone = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };
	std::vector<int> czarne = { 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35 };


	//Mouse positions
	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;
	
	//Bet type 
	enum class BetType
	{
		Number,
		Red,
		Black,
		Range1To12,
		Range13To24,
		Range25To36
	};

	struct Bet
	{
		BetType type;
		int number; // W przypadku typu Number, przechowuje wybran¹ liczbê
	};

	const int TableSize = 36;

	// Utworzenie struktur reprezentuj¹cych pola na stole
	struct TableField
	{
		sf::RectangleShape shape;
		sf::Text numberText;
	};

	// Funkcja sprawdzaj¹ca, czy wygrana dla danego numeru
	bool IsWinningNumber(int number, const Bet& bet)
	{
		switch (bet.type)
		{
		case BetType::Number:
			return number == bet.number;
		case BetType::Red:
			for (int i = 0; i < TableSize; ++i) {
				//std::cout << number << std::endl;
				if (czerwone[i] == number)
					return number;
			}
				return number;
		case BetType::Black:
			for (int i = 0; i < TableSize; ++i) {
				//std::cout << i << std::endl;
				if (czarne[i] == number)
					return number;
			}
		case BetType::Range1To12:
			return (number >= 1 && number <= 12);
		case BetType::Range13To24:
			return (number >= 13 && number <= 24);
		case BetType::Range25To36:
			return (number >= 25 && number <= 36);
		default:
			return false;
		}
	}

	//Textures  
	sf::Texture coin10Tex;
	sf::Texture coin20Tex;
	sf::Texture coin50Tex;
	sf::Texture coin100Tex;
	sf::Texture coin200Tex;
	sf::Texture coin500Tex;

	sf::Texture wheelTex;
	sf::Sprite wheelSprite;

	sf::Sprite coin10Sprite; 
	sf::Sprite coin20Sprite; 
	sf::Sprite coin50Sprite; 
	sf::Sprite coin100Sprite; 
	sf::Sprite coin200Sprite; 
	sf::Sprite coin500Sprite; 

	sf::Texture texture;
	sf::Sprite background;

	//Game objects
	UImodel botBar;
	//UImodel botBar2;
	//UImodel botBar3;
	//UImodel botBar4;
	//UImodel botBar5;
	//UImodel botBar6;
	//UImodel botBar7;
	//UImodel botBar8;

	//Roulette model 
	std::vector<TableField> tableFields;
	Bet playerBet;
	sf::RectangleShape redField;
	sf::RectangleShape blackField;
	sf::RectangleShape range1to12Field;
	sf::RectangleShape range13to24Field;
	sf::RectangleShape range25to36Field;
	sf::RectangleShape evenField;
	sf::RectangleShape oddField;
 
	//Random number 
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dist;

	//Player object 
	player p1; 
	int a = 10;

	//Wheel animation
	sf::IntRect currentFrame; 

	//text
	uiText tekst1;
	uiText tekst2;
	uiText tekst3;
	
	//Private functions 
	void initVar(); 
	void initWindow(); 
	void initBackground();
	void initTextures();
	void initBar();
	void initWheelTex();
	void initAnimation(); 
	void initTableField(); 
	void initRandom(); 
	void initGrid(); 
	

public:
	//Constructor and destructor 
	game(); 
	virtual ~game(); 

	//Accessors 
	const bool isRunning() const; 
 
	sf::Font font;
	void initFont();

	sf::Text tekst;

	//Functions 
	void pollEvents(); 
	void updateMousePositions(); 
	void updateText();
	void updateAnimation();
	void update(); 

	//Renders
	void renderText(sf::RenderTarget& target);
	void renderBar(); 
	void renderBackground(); 
	void renderCoins();
	void renderWheel();
	void renderGrid();
	void renderTableField();
	void render();

	void rouletteFunc(); 

	void colorChange();
};