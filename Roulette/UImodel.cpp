#include "UImodel.h"


UImodel::UImodel() {}

UImodel::UImodel(float posx, float posy, float sizex, float sizey) {
    //sizePos(posx, posy, sizex, sizey);

    this->stats.setPosition(posx, posy);
    this->stats.setSize(sf::Vector2f(sizex, sizey));
    this->stats.setFillColor(sf::Color::Blue);
    this->stats.setOutlineColor(sf::Color::Green);
    this->stats.setOutlineThickness(1.f);
}