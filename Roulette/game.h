#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <chrono>
#include <thread>
#include <filesystem>


#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "UImodel.h"
#include "uiText.h"
#include "player.h"
#include "animation.h"


//	TODO
//	-  
//	- 

/*
	Class with the game engine
*/

class game
{
protected:
	//Variable
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event eve;
	sf::Event eve2;
	std::vector<UImodel> botBars;
	bool mouseHeld = false;
	bool mouseHeld2 = false;
	bool mouseHeld3 = false;
	bool mouseHeld4 = false;
	bool buttonHeld = false;
	bool buttonHeld2 = false;
	bool buttonHeld3 = false;
	std::vector<int> czerwone = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };
	std::vector<int> czarne = { 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35 };
	std::vector<int> range1to12 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	std::vector<int> range13to24 = { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	std::vector<int> range25to36 = { 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36 };

	std::vector<int> betNumbers; 

	//Struktura BetType aby wiedziec jaki typ betu mamy
	struct BetType {
		std::string name;  // Nazwa rodzaju obstawiania
		int payout;        // Wspó³czynnik wyp³aty

		// Konstruktor
		BetType(const std::string& _name, int _payout)
			: name(_name), payout(_payout) {}
	};
	std::vector<BetType> betTypes;

	//Menu
	static const int MAX_OPTIONS = 10;
	sf::Text menuTexts[MAX_OPTIONS];
	int selectedItemIndex;

	void initMenuText();
	void menuSwitch();
	bool io = false; 
	bool settings = true; 
	void settingsInfo(); 

	//Nickname & save
	std::string nickname; 
	sf::Event textEvent;
	
	//Mouse positions
	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;

	const int TableSize = 36;

	// Utworzenie struktur reprezentuj¹cych pola na stole
	struct TableField
	{
		sf::RectangleShape shape;
		sf::Text numberText;
	};

	//Textures  
	sf::Texture coin10Tex;
	sf::Texture coin20Tex;
	sf::Texture coin50Tex;
	sf::Texture coin100Tex;
	sf::Texture coin200Tex;
	sf::Texture coin500Tex;

	//sf::Texture wheelTex;
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

	//Roulette model 
	std::vector<TableField> tableFields;
	UImodel redField;
	UImodel blackField;
	UImodel range1to12Field;
	UImodel range13to24Field;
	UImodel range25to36Field;
	UImodel evenField;
	UImodel oddField;

	//Random number 
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dist;
	int randomNum; 

	//Player object 
	player p1;
	int a = 10;

	//Wheel animation
	sf::Texture wheelTex;
	sf::Texture wheelTex2;
	sf::RectangleShape wheel;
	sf::RectangleShape wheel2;
	sf::IntRect currentFrame;
	animation Animation;
	float time = 0.4f;
	bool playPause = 0;
	bool animWheel = false;
	void rotateWheel(); 
	int row = 0;
	float deltaTime = 0.0f;



	//text
	uiText tekst1;
	uiText tekst2;
	uiText tekst3;
	uiText tekst4;
	uiText tekst5;
	std::string tekst5text;
	uiText tekst6;
	uiText tekst7;
	uiText tekst8;
	uiText tekst9;
	uiText tekst10;
	uiText tekst11;
	uiText tekst12;
	uiText tekst13;
	uiText tekst14;
	uiText tekst15;
	uiText tekst16;
	std::string winText; 
	std::string rankText;

	 
	//Private functions 
	void initVar();
	void initWindow();
	void initBackground();
	void initTextures();
	void initBar();
	void initWheelTex();
	void initTableField();
	void initRandom();
	void initWheelSpin();


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
	void renderMenu();
	void renderBar();
	void renderBackground();
	void renderCoins();
	void renderWheel();
	void renderGrid();
	void renderTableField();
	void render();
	void render2();
	void menuParts();

	void rouletteFunc();

	void bet(); 
	void wheelSpin(); 

	int winAmount = 0;
	int maxwin; 
	void maxWin();

	void colorChange();

	
};