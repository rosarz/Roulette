#include "game.h"

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

void game::initTextures()
{
    if (!coin10Tex.loadFromFile("assets/10.png"))
        std::cout << "Error: Failed to load 10 Coin"; 

    if (!coin20Tex.loadFromFile("assets/20.png"))
        std::cout << "Error: Failed to load 20 Coin";

    if (!coin50Tex.loadFromFile("assets/50.png"))
        std::cout << "Error: Failed to load 50 Coin";

    if (!coin100Tex.loadFromFile("assets/100.png"))
        std::cout << "Error: Failed to load 100 Coin";

    if (!coin200Tex.loadFromFile("assets/200.png"))
        std::cout << "Error: Failed to load 200 Coin";

    if (!coin500Tex.loadFromFile("assets/500.png"))
        std::cout << "Error: Failed to load 500 Coin";

    this->coin10Sprite.setTexture(coin10Tex);
    this->coin10Sprite.setPosition(780.f, 590.f);
    this->coin10Sprite.scale(2.f, 2.f);

    this->coin20Sprite.setTexture(coin20Tex);
    this->coin20Sprite.setPosition(850.f, 590.f);
    this->coin20Sprite.scale(2.f, 2.f);

    this->coin50Sprite.setTexture(coin50Tex);
    this->coin50Sprite.setPosition(930.f, 590.f);
    this->coin50Sprite.scale(2.f, 2.f);
    
    this->coin100Sprite.setTexture(coin100Tex);
    this->coin100Sprite.setPosition(1000.f, 590.f);
    this->coin100Sprite.scale(2.f, 2.f);
    
    this->coin200Sprite.setTexture(coin200Tex);
    this->coin200Sprite.setPosition(1075.f, 590.f);
    this->coin200Sprite.scale(2.f, 2.f);
    
    this->coin500Sprite.setTexture(coin500Tex);
    this->coin500Sprite.setPosition(1145.f, 590.f);
    this->coin500Sprite.scale(2.f, 2.f);
}

void game::initBar()
{
    botBar = UImodel(510.0f, 590.0f, 110.f, 70.0f);

    //botBar2 = UImodel(197.5f, 585.0f, 147.5f, 70.0f);
    //botBar3 = UImodel(345.0f, 585.0f, 147.5f, 70.0f);
    //botBar4 = UImodel(492.5f, 585.0f, 147.5f, 70.0f);
    //botBar5 = UImodel(640.0f, 585.0f, 147.5f, 70.0f);
    //botBar6 = UImodel(787.5f, 585.0f, 147.5f, 70.0f);
    //botBar7 = UImodel(935.0f, 585.0f, 147.5f, 70.0f);
    //botBar8 = UImodel(1082.5f, 585.0f, 147.5f, 70.0f);

    //botBars.push_back(botBar);
    //botBars.push_back(botBar2);
    //botBars.push_back(botBar3);
    //botBars.push_back(botBar4);
    //botBars.push_back(botBar5);
    //botBars.push_back(botBar6);
    //botBars.push_back(botBar7);
    //botBars.push_back(botBar8);
}

void game::initWheelTex()
{
    if (!wheelTex.loadFromFile("assets/wheelsheet.png"))
    {
        std::cout << "Error::initFonts()::Failed to wheel texture from game.cpp\n";
    }
    else
        std::cout << "Wheel texture loaded from game.cpp\n";

    this->wheelSprite.setTexture(this->wheelTex);
    this->wheelSprite.setPosition(150.f, 200.f);
    this->currentFrame = sf::IntRect(0, 0, 220, 205); 
    this->wheelSprite.setTextureRect(this->currentFrame);
    this->wheelSprite.scale(1.5f, 1.5f);
    //this->currentFrame
}

void game::initFont()
{
    if (!font.loadFromFile("Font/KongtextRegular-q36q.ttf"))
    {
        std::cout << "Error::initFonts()::Failed to load font from game.cpp\n";
    }
    else
        std::cout << "Font loaded from game.cpp\n";
}

void game::initAnimation()
{

}

void game::initTableField()
{
    // Inicjalizacja pola tableField dla ka¿dej liczby na stole
    tableFields = std::vector<TableField>(TableSize);

    for (int i = 0; i < TableSize; ++i)
    {
        tableFields[i].shape.setSize(sf::Vector2f(50, 50));
        for (int a : czerwone){
            std::cout << a << std::endl; 
            if (a == i)
                tableFields[i].shape.setFillColor(sf::Color::Red);
        }
        for (int a : czarne) {
            std::cout << a << std::endl;
            if (a == i)
                tableFields[i].shape.setFillColor(sf::Color::Black);
        }
        tableFields[i].shape.setOutlineColor(sf::Color::Black);
        tableFields[i].shape.setOutlineThickness(1.5f);
        tableFields[i].shape.setPosition(540 + (i % 12) * 60, 200 + (i / 12) * 60);

        tableFields[i].numberText.setFont(font);
        tableFields[i].numberText.setString(std::to_string(i + 1));
        tableFields[i].numberText.setFillColor(sf::Color::White);
        tableFields[i].numberText.setCharacterSize(16);
        tableFields[i].numberText.setPosition(tableFields[i].shape.getPosition().x + 15, tableFields[i].shape.getPosition().y + 15);
        if(i >= 9)
            tableFields[i].numberText.setPosition(tableFields[i].shape.getPosition().x + 8, tableFields[i].shape.getPosition().y + 15);

    }
}

void game::initRandom()
{
    // Inicjalizacja generatora liczb pseudolosowych
    rd;
    gen = std::mt19937(rd());
    dist = std::uniform_int_distribution<>(0, TableSize - 1);
}


//Constructor 
game::game() : tekst1(24, sf::Color::Color(45, 147, 108), "ss.str()", 60.f, 610.f),
               tekst2(24, sf::Color::Color(45, 147, 108), "ss2.str()", 300.f, 610.f),
               tekst3(24, sf::Color::Color(45, 147, 108), "Undo\nbet", 520.f, 600.f)
{
	this->initVar(); 
	this->initWindow(); 
    this->initBackground();  
    this->initBar(); 
    this->initFont(); 
    this->initTextures();
    this->initWheelTex();
    this->initTableField();
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
    std::cout << "Mouse X: " << mousePos.x << " Mouse Pos Y: " << mousePos.y << "\n";
}

void game::updateText()
{
    std::stringstream ss;
    std::stringstream ss2;
    ss << "Cash:" << p1.money;
    ss2 << "Bet:" << p1.bet;

    tekst1._text.setString(ss.str());
    tekst2._text.setString(ss2.str());
}

void game::updateAnimation()
{

}

//Update the game logic 
void game::update()
{
    //Game close logic
    this->pollEvents(); 

    this->updateText();

    //Update mouse position 
    this->updateMousePositions(); 
}


void game::renderText(sf::RenderTarget &target) // w tej formie dzia³a uiText tekst1(24, sf::Color::Red, "Cash:1337", 60.f, 610.f);
{
    //uiText tekst3(24, sf::Color::Red, "O O O", 650.f, 610.f);
    //uiText tekst4(24, sf::Color::Red, "O O O", 945.f, 610.f);
    
    //jak zrobie to jako obiekt lokalny to dzia³a ok 
    //ale jako obiekt w pliku nag³ówkowym nie dzia³a 
    //tak nie dzia³a nie wiem czemu
    //tekst1 = uiText(24, sf::Color::Red, "Cash:1337", 60.f, 610.f);
    //tekst2 = uiText(24, sf::Color::Red, "Bet:2137", 355.f, 610.f);
    //tekst3 = uiText(24, sf::Color::Red, "O O O", 650.f, 610.f);
    //tekst4 = uiText(24, sf::Color::Red, "O O O", 945.f, 610.f);
    //Text objects		//lokalnie w metodzie dzia³a
    //uiText tekst1;
    //uiText tekst2;
    //uiText tekst3;
    //uiText tekst4;

    target.draw(tekst1._text);
    target.draw(tekst2._text);
    target.draw(tekst3._text);
    //target.draw(tekst4._text);
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
    this->rouletteFunc();
    this->renderBackground(); 
    this->renderBar(); 
    this->renderText(*this->window);
    this->colorChange();
    this->updateText(); 
    this->renderCoins();
    this->renderWheel();
    this->rouletteFunc();
    
    
    this->window->display();
}

//Render of all bottom stats
void game::renderBar()
{ 
    this->window->draw(botBar.stats);
    //this->window->draw(botBar2.stats);
    //this->window->draw(botBar3.stats);
    //this->window->draw(botBar4.stats);
    //this->window->draw(botBar5.stats);
    //this->window->draw(botBar6.stats);
    //this->window->draw(botBar7.stats);
    //this->window->draw(botBar8.stats);
}

void game::renderBackground()
{
    //init 
    this->background.setTexture(texture);

    //draw
    this->window->draw(background);
}

void game::renderCoins()
{
    this->window->draw(coin10Sprite); 
    this->window->draw(coin20Sprite); 
    this->window->draw(coin50Sprite); 
    this->window->draw(coin100Sprite); 
    this->window->draw(coin200Sprite); 
    this->window->draw(coin500Sprite); 
}

void game::renderWheel()
{
    this->window->draw(wheelSprite); 
}

void game::colorChange()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false) 
        {
            mouseHeld = true; 
            //for (auto& bar : botBars) { //for by³ wczeœniej do skrócenia tych instrukcji if ale nie wiem jak zrobiæ aby nie by³o kilkukrotnego wywo³ania wszystkich instrukcji wiêc zostawiam tak 
                if (coin10Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 10) {
                    std::cout << "Zwiekszono bet o 10\n";
                    p1.bet += 10; 
                    p1.money -= 10; 
                    std::cout << "Bet: " << p1.bet << "\nCash: " << p1.money << std::endl;
                }
                if (coin20Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 20) {
                    std::cout << "Zwiekszono bet o 20\n";
                    p1.bet += 20;
                    p1.money -= 20;
                }
                if (coin50Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 50) {
                    std::cout << "Zwiekszono bet o 50\n";
                    p1.bet += 50;
                    p1.money -= 50;
                }
                if (coin100Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 100) {
                    std::cout << "Zwiekszono bet o 100\n";
                    p1.bet += 100;
                    p1.money -= 100;
                }
                if (coin200Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 200) {
                    std::cout << "Zwiekszono bet o 200\n";
                    p1.bet += 200;
                    p1.money -= 200;
                }
                if (coin500Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 500) {
                    std::cout << "Zwiekszono bet o 500\n";
                    p1.bet += 500;
                    p1.money -= 500;
                }
                if (botBar.stats.getGlobalBounds().contains(this->mousePosView)) {
                    std::cout << "Wyzerowano bet";
                    p1.last_bet = p1.bet;
                    p1.bet = 0;
                    std::cout << p1.last_bet << std::endl;
                    p1.money += p1.last_bet;
                    p1.last_bet = 0;
                    std::cout << p1.last_bet << std::endl;
                }
            //}
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (this->mouseHeld == false)
        {
            mouseHeld = true; 
            if (coin10Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 10) {
                std::cout << "Zmniejszono bet o 10\n";
                p1.bet -= 10;
                p1.money += 10;
                std::cout << "Bet: " << p1.bet << "\n Cash: " << p1.money;
            }
            if (coin20Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 20) {
                std::cout << "Zmniejszono bet o 20\n";
                p1.bet -= 20;
                p1.money += 20;
            }
            if (coin50Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 50) {
                std::cout << "Zmniejszono bet o 50\n";
                p1.bet -= 50;
                p1.money += 50;
            }
            if (coin100Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 100) {
                std::cout << "Zmniejszono bet o 100\n";
                p1.bet -= 100;
                p1.money += 100;
            }
            if (coin200Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 200) {
                std::cout << "Zmniejszono bet o 200\n";
                p1.bet -= 200;
                p1.money += 200;
            }
            if (coin500Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 500) {
                std::cout << "Zmniejszono bet o 500\n";
                p1.bet -= 500;
                p1.money += 500;
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void game::rouletteFunc()
{
    if (eve.type == sf::Event::MouseButtonPressed)
    {
        if (eve.mouseButton.button == sf::Mouse::Left)
        {
            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu sto³u
            for (int i = 0; i < TableSize; ++i)
            {
                if (tableFields[i].shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    playerBet.type = BetType::Number;
                    playerBet.number = i + 1;
                    break;
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu czerwonym
            redField = sf::RectangleShape(sf::Vector2f(50, 50));
            redField.setFillColor(sf::Color::Red);
            redField.setPosition(600, 420);
            if (redField.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                playerBet.type = BetType::Red;
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu czarnym
            blackField = sf::RectangleShape(sf::Vector2f(50, 50));
            blackField.setFillColor(sf::Color::Black);
            blackField.setPosition(670, 420);
            if (blackField.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                playerBet.type = BetType::Black;
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 1-12
            range1to12Field = sf::RectangleShape(sf::Vector2f(50, 50));
            range1to12Field.setFillColor(sf::Color::White);
            range1to12Field.setOutlineColor(sf::Color::Black);
            range1to12Field.setOutlineThickness(1.0f);
            range1to12Field.setPosition(740, 420);
            if (range1to12Field.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                playerBet.type = BetType::Range1To12;
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 13-24
            range13to24Field = sf::RectangleShape(sf::Vector2f(50, 50));
            range13to24Field.setFillColor(sf::Color::White);
            range13to24Field.setOutlineColor(sf::Color::Black);
            range13to24Field.setOutlineThickness(1.0f);
            range13to24Field.setPosition(810, 420);
            if (range13to24Field.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                playerBet.type = BetType::Range13To24;
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 25-36
            range25to36Field = sf::RectangleShape(sf::Vector2f(50, 50));
            range25to36Field.setFillColor(sf::Color::White);
            range25to36Field.setOutlineColor(sf::Color::Black);
            range25to36Field.setOutlineThickness(1.0f);
            range25to36Field.setPosition(880, 420);
            if (range25to36Field.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                playerBet.type = BetType::Range25To36;
            }

            //Sprawdzenie czy klikniecie bylo na polu parzyste
            evenField = sf::RectangleShape(sf::Vector2f(50, 50));
            evenField.setFillColor(sf::Color::White);
            evenField.setOutlineColor(sf::Color::Black);
            evenField.setOutlineThickness(1.0f);
            evenField.setPosition(880, 420);

            //Sprawdzenie czy klikniecie bylo na polu nieparzyste
            oddField = sf::RectangleShape(sf::Vector2f(50, 50));
            oddField.setFillColor(sf::Color::White);
            oddField.setOutlineColor(sf::Color::Black);
            oddField.setOutlineThickness(1.0f);
            oddField.setPosition(880, 420);
        }
    }

    //this->window->clear(sf::Color(0, 128, 0));

    // Rysowanie sto³u z cyframi
    for (int i = 0; i < TableSize; ++i)
    {
        this->window->draw(tableFields[i].shape);
        this->window->draw(tableFields[i].numberText);
    }

    // Rysowanie pól do obstawiania
    sf::RectangleShape redField(sf::Vector2f(50, 50));
    redField.setFillColor(sf::Color::Red);
    redField.setPosition(600, 420);
    this->window->draw(redField);

    sf::RectangleShape blackField(sf::Vector2f(50, 50));
    blackField.setFillColor(sf::Color::Black);
    blackField.setPosition(670, 420);
    this->window->draw(blackField);

    sf::RectangleShape range1to12Field(sf::Vector2f(50, 50));
    range1to12Field.setFillColor(sf::Color::White);
    range1to12Field.setOutlineColor(sf::Color::Black);
    range1to12Field.setOutlineThickness(1.0f);
    range1to12Field.setPosition(740, 420);
    this->window->draw(range1to12Field);

    sf::RectangleShape range13to24Field(sf::Vector2f(50, 50));
    range13to24Field.setFillColor(sf::Color::White);
    range13to24Field.setOutlineColor(sf::Color::Black);
    range13to24Field.setOutlineThickness(1.0f);
    range13to24Field.setPosition(810, 420);
    this->window->draw(range13to24Field);

    sf::RectangleShape range25to36Field(sf::Vector2f(50, 50));
    range25to36Field.setFillColor(sf::Color::White);
    range25to36Field.setOutlineColor(sf::Color::Black);
    range25to36Field.setOutlineThickness(1.0f);
    range25to36Field.setPosition(880, 420);
    this->window->draw(range25to36Field);

    // Sprawdzenie, czy wybrana liczba odpowiada wylosowanej liczbie ruletki
    int winningNumber = dist(gen);
    for (int i = 0; i < TableSize; ++i)
    {
        if (IsWinningNumber(i + 1, playerBet))
        {
            tableFields[i].shape.setOutlineColor(sf::Color::Green);
        }
        else
        {
            tableFields[i].shape.setOutlineColor(sf::Color::Black);
        }
    }
}