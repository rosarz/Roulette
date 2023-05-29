#include "game.h"

//Private functions 
//
void game::initVar()
{
	this->window = nullptr; 
	
}

void game::initWindow()
{
	this->videoMode.height = 720; 
	this->videoMode.width = 1280; 
	this->window = new sf::RenderWindow(this->videoMode, "Roulette", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(144); 
}

void game::initFonts()
{
    if (this->font.loadFromFile("Font/PressStartRegular - ay8E.ttf"))
    {
        std::cout << "Error::initFonts()::Failed to load font" << std::endl; 
    }
}

void game::initText()
{
    this->uiText.setFont(this->font); 
    this->uiText.setCharacterSize(12); 
    this->uiText.setFillColor(sf::Color::White); 
    this->uiText.setString("AAAAA"); 
}

void game::initEnemies() //z tego zrobic pasek z kasa, betem itd itd 
{
    this->enemy.setPosition(50.f, 585.f);
    this->enemy.setSize(sf::Vector2f(1200.f, 70.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

void game::initStats()
{
    this->enemy.setPosition(50.f, 585.f);
    this->enemy.setSize(sf::Vector2f(1200.f, 70.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

//Constructor 
game::game()
{
	this->initVar(); 
	this->initWindow(); 
    this->initEnemies(); 
    this->initStats(); 
    this->initText(); 
    this->colorChange(); 
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
            if (this->eve.key.code = sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void game::updateMousePositions()
{
    /*
    @return void 

    Updates the mouse positions: 
        - Mouse positions relative to window (vector2i) 
    */

    this->mousePos = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePos);
}

void game::updateText()
{

}

void game::updateEnemies()
{
    
}

//Update the game logic 
void game::update()
{
    this->pollEvents(); 

    
    //Update mouse position 
    this->updateMousePositions(); 

    this->updateEnemies(); 
    this->updateStats(); 
}

void game::updateStats()
{

}

void game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText); 
}

void game::renderEnemies()
{
    this->window->draw(enemy); 
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
    this->renderEnemies();

    //this->renderStats(); 
    this->renderText(*this->window);
    //this->colorChange(); 

    this->window->display();
}

void game::renderStats()
{
    this->window->draw(stats); 
}

void game::colorChange()
{
    if (eve.type == sf::Event::MouseButtonPressed)
        if(eve.key.code == sf::Mouse::Left)
            if (enemy.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                this->enemy.setFillColor(sf::Color::Red);
            }

}


