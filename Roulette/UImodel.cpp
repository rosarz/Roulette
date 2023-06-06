#include "UImodel.h"


UImodel::UImodel() {}

UImodel::UImodel(float posx, float posy, float sizex, float sizey) 
{
    this->stats.setPosition(posx, posy);
    this->stats.setSize(sf::Vector2f(sizex, sizey));
    this->stats.setFillColor(sf::Color::Transparent);
    //this->stats.setOutlineColor(sf::Color::Red);
    this->stats.setOutlineThickness(1.f);
}