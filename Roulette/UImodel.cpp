#include "UImodel.h"


void UImodel::initStats()
{
    this->stats.setPosition(50.f, 585.f);
    this->stats.setSize(sf::Vector2f(1200.f, 70.f));
    this->stats.setFillColor(sf::Color::Blue);
    this->stats.setOutlineColor(sf::Color::Green);
    this->stats.setOutlineThickness(1.f);
}

void UImodel::renderStats()
{
    //this->window->draw(stats);
}