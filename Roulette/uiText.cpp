#include "uiText.h"


uiText::uiText()
{

}

uiText::uiText(int size, sf::Color color, std::string text, float x, float y)
{
    initFont();
    this->_text.setFont(font);
    this->_text.setCharacterSize(size);
    this->_text.setFillColor(color);
    this->_text.setString(text);
    this->_text.setPosition(x, y);
}

void uiText::initFont()
{
    if (!font.loadFromFile("Font/PressStartRegular.ttf"))
    {
        std::cout << "Error::initFonts()::Failed to load font" << std::endl;
    }
}