#include "game.h"

//Private functions 
//
void game::initVar()
{
	this->window = nullptr; 
    this->mouseHeld = false;
}

void game::initWindow()
{
	this->videoMode.height = 720; 
	this->videoMode.width = 1280; 
	this->window = new sf::RenderWindow(this->videoMode, "Roulette", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144); 
}

void game::initBackground()
{
    if (!texture.loadFromFile("assets/tlo.png"))
    {
        std::cout << "Error: Failed to load texture\n"; 
    }
}

void game::initBar()
{
    botBar = UImodel(50.0f, 585.0f, 147.5f, 70.0f);
    botBar2 = UImodel(197.5f, 585.0f, 147.5f, 70.0f);
    botBar3 = UImodel(345.0f, 585.0f, 147.5f, 70.0f);
    botBar4 = UImodel(492.5f, 585.0f, 147.5f, 70.0f);
    botBar5 = UImodel(640.0f, 585.0f, 147.5f, 70.0f);
    botBar6 = UImodel(787.5f, 585.0f, 147.5f, 70.0f);
    botBar7 = UImodel(935.0f, 585.0f, 147.5f, 70.0f);
    botBar8 = UImodel(1082.5f, 585.0f, 147.5f, 70.0f);

    botBars.push_back(botBar);
    botBars.push_back(botBar2);
    botBars.push_back(botBar3);
    botBars.push_back(botBar4);
    botBars.push_back(botBar5);
    botBars.push_back(botBar6);
    botBars.push_back(botBar7);
    botBars.push_back(botBar8);
}

void game::initFont()
{
    if (!font.loadFromFile("Font/PressStartRegular.ttf"))
    {
        std::cout << "Error::initFonts()::Failed to load font from game.cpp" << std::endl;
    }
    else
        std::cout << "Font loaded from game.cpp";
}

//Constructor 
game::game()
{
	this->initVar(); 
	this->initWindow(); 
    this->initBackground();  
    this->initBar(); 
    this->initFont(); 
}
//Deconstructor
game::~game()
{
	delete this->window; 
}

//Accessors 
const bool game::isRunning() const
{
	return this->window->isOpen();
}

//Functions 
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

//Updates the mouse positions on console
void game::updateMousePositions()
{
    this->mousePos = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePos);
    //std::cout << "Mouse X: " << mousePos.x << " Mouse Pos Y: " << mousePos.y << "\n";
}

void game::updateText()
{

}

//Update the game logic 
void game::update()
{
    //Game close logic
    this->pollEvents(); 

    //Update mouse position 
    this->updateMousePositions(); 
}


void game::renderText(sf::RenderTarget &target) // w tej formie dzia³a uiText tekst1(24, sf::Color::Red, "Cash:1337", 60.f, 610.f);
{
    //jak zrobie to jako obiekt lokalny to dzia³a ok 
    //ale jako obiekt w pliku nag³ówkowym nie dzia³a 
    //naprawiæ!

    tekst1 = uiText(24, sf::Color::Red, "Cash:1337", 60.f, 610.f);
    tekst2 = uiText(24, sf::Color::Red, "Bet:2137", 355.f, 610.f);
    tekst3 = uiText(24, sf::Color::Red, "O O O", 650.f, 610.f);
    tekst4 = uiText(24, sf::Color::Red, "O O O", 945.f, 610.f);

    target.draw(tekst1._text);
    target.draw(tekst2._text);
    target.draw(tekst3._text);
    target.draw(tekst4._text);
}

void game::render()
{
    /*
    @return void
    Render the game objects
    - clear old frame
    - render objects
    - display frame in window
    */

    this->window->clear();

    //Draw the game
    this->renderBackground(); 
    
    this->renderBar(); 
    
    this->renderText(*this->window);

    this->colorChange();
    
    this->window->display();
}

//Render of all bottom stats
void game::renderBar()
{ 
    this->window->draw(botBar.stats);
    this->window->draw(botBar2.stats);
    this->window->draw(botBar3.stats);
    this->window->draw(botBar4.stats);
    this->window->draw(botBar5.stats);
    this->window->draw(botBar6.stats);
    this->window->draw(botBar7.stats);
    this->window->draw(botBar8.stats);
}

void game::renderBackground()
{
    background.setTexture(texture);

    this->window->draw(background);
}


void game::colorChange()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    {
        if (this->mouseHeld == false) 
        {
            mouseHeld = true; 
            //for (auto& bar : botBars) {
                if (botBar.stats.getGlobalBounds().contains(this->mousePosView)) {
                    std::cout << "Currency reduced\n";
                    //botBar.stats.setFillColor(sf::Color::White);
                    //window->draw(bar.stats);
                    //break;
                }
                if (botBar2.stats.getGlobalBounds().contains(this->mousePosView)) {
                    std::cout << "Currency increased\n";
                    
                }
                if (botBar3.stats.getGlobalBounds().contains(this->mousePosView)) {
                    std::cout << "Bet reduced\n";

                }
                if (botBar4.stats.getGlobalBounds().contains(this->mousePosView)) {
                    std::cout << "Bet increased\n";

                }
            //}
        }
    }
    else
        this->mouseHeld = false;
}