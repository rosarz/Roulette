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


/*
void game::pollEvents()
{
    while (this->window->pollEvent(this->eve))
    {
        switch (this->eve.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->eve.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;

        }
    }
}
*/