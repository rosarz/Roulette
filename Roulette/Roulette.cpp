#include "roulette.h"

roulette::roulette(std::string textureName, float x, float y, bool loaded, bool exit)
{
	pos = sf::Vector2f(x, y); 
	sprite.setPosition(pos); 
	//isLoaded = loaded;
	//isExit = exit; 
}

bool roulette::isLoaded()
{

}

bool roulette::isExit() 
{

}

bool roulette::setTexture(std::string) 
{

}