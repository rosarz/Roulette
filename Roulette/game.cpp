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

     for (int i = 0; i < 36; ++i)
    {
        tableFields[i].shape.setSize(sf::Vector2f(50, 50));
        tableFields[i].shape.setFillColor(sf::Color::Red);
        
        tableFields[i].shape.setOutlineColor(sf::Color::Black);
        tableFields[i].shape.setOutlineThickness(1.5f);
        tableFields[i].shape.setPosition(540 + (i % 12) * 60, 200 + (i / 12) * 60);

        tableFields[i].numberText.setFont(font);
        tableFields[i].numberText.setString(std::to_string(i + 1));
        tableFields[i].numberText.setFillColor(sf::Color::White);
        tableFields[i].numberText.setCharacterSize(16);
        tableFields[i].numberText.setPosition(tableFields[i].shape.getPosition().x + 15, tableFields[i].shape.getPosition().y + 15);
        if (i >= 9)
            tableFields[i].numberText.setPosition(tableFields[i].shape.getPosition().x + 8, tableFields[i].shape.getPosition().y + 15);
        //tableFields[0].shape.setFillColor(sf::Color::Red);
    }

     for (auto kcza : czarne) {
         tableFields[kcza-1].shape.setFillColor(sf::Color::Black);
     }
}

void game::initRandom()
{
    // Inicjalizacja generatora liczb pseudolosowych
    rd;
    gen = std::mt19937(rd());
    dist = std::uniform_int_distribution<>(0, TableSize - 1);
    
    //randomNum = dist(gen); 
    randomNum = 3;
    std::cout << randomNum; 
}


//Constructor 
game::game() : tekst1(24, sf::Color::Color(45, 147, 108), "ss.str()", 60.f, 610.f),
tekst2(24, sf::Color::Color(45, 147, 108), "ss2.str()", 300.f, 610.f),
tekst3(24, sf::Color::Color(45, 147, 108), "Undo\nbet", 520.f, 600.f),
tekst4(30, sf::Color::Color(45, 147, 108), "SPIN", 1020.f, 440.f),
tekst5(30, sf::Color::Color(45, 147, 108), "ss3.str()", 350.f, 110.f),
tekst6(30, sf::Color::Color(45, 147, 108), "EXIT", 1140.f, 20.f),
tekst7(90, sf::Color::Color(45, 147, 108), "ROULETTE", 320.f, 210.f)
{
    this->initMenuText(); 
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
            if (this->eve.key.code == sf::Keyboard::Escape){
                io = false; 
                this->window->clear();
            }
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
    std::stringstream ss;
    std::stringstream ss2;
    std::stringstream ss3;
    
    ss << "Cash:" << p1.money;
    ss2 << "Bet:" << p1.bet;
    ss3 << tekst5text;

    tekst1._text.setString(ss.str());
    tekst2._text.setString(ss2.str());
    tekst5._text.setString(ss3.str());
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

    this->menuSwitch();
}

void game::renderText(sf::RenderTarget& target) // w tej formie dzia³a uiText tekst1(24, sf::Color::Red, "Cash:1337", 60.f, 610.f);
{
    target.draw(tekst1._text);
    target.draw(tekst2._text);
    target.draw(tekst3._text);
    target.draw(tekst4._text);
    target.draw(tekst5._text);
    target.draw(tekst6._text);
}

void game::initMenuText()
{
    menuTexts[0].setFont(font);
    menuTexts[0].setFillColor(sf::Color::Color(45, 147, 108));
    menuTexts[0].setString("Start");
    menuTexts[0].setPosition(sf::Vector2f(570, 350));

    menuTexts[1].setFont(font);
    menuTexts[1].setFillColor(sf::Color::Color(45, 147, 108));
    menuTexts[1].setString("Settings");
    menuTexts[1].setPosition(sf::Vector2f(530, 420));

    menuTexts[2].setFont(font);
    menuTexts[2].setFillColor(sf::Color::Color(45, 147, 108));
    menuTexts[2].setString("Exit");
    menuTexts[2].setPosition(sf::Vector2f(585, 490));
}

void game::renderMenu()
{
    for(int i = 0; i < MAX_OPTIONS; i++)
    {
        this->window->draw(menuTexts[i]);
    }
    this->window->draw(tekst7._text);
}

void game::menuSwitch()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        if (this->buttonHeld == false)
        {
            buttonHeld = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                std::cout << "Klawisz w gore";
                menuTexts[selectedItemIndex].setFillColor(sf::Color::Color(45, 147, 108));
                selectedItemIndex--;
                menuTexts[selectedItemIndex].setFillColor(sf::Color::White);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                std::cout << "Klawisz w dol";
                menuTexts[selectedItemIndex].setFillColor(sf::Color::Color(45, 147, 108));
                selectedItemIndex++;
                menuTexts[selectedItemIndex].setFillColor(sf::Color::White);
            }
        }
    }
    else
    {
        this->buttonHeld = false;
    }
}

void game::menuParts()
{
    if (this->buttonHeld2 == false)
    {
        this->buttonHeld2 = true;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && selectedItemIndex == 0)
        {
            io = true;
            std::cout << "0\n";
            //this->window->clear();
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && selectedItemIndex == 1)
        {
            this->window->clear(); 
            tekst5text = "Unfortunatelly right now\nwe can't change settings";
            this->window->draw(tekst5._text);
            std::cout << "1\n";
            std::chrono::seconds dura(5);
            std::this_thread::sleep_for(dura);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && selectedItemIndex == 2)
        {
            this->window->close();
            std::cout << "2\n";
        }
    }
    else
    {
        this->buttonHeld2 = false;
    }
}

void game::render()
{
    if (io == true) {
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
    this->updateText();
    this->renderCoins();
    this->renderWheel();
    this->rouletteFunc();
    this->wheelSpin();


    this->window->display();
    }
}

void game::render2()
{
    if (io == false)
    {
        this->window->clear();

        this->menuParts();
        this->renderBackground();
        this->renderMenu();
        
        this->window->display();
    }
}

//Render of all bottom stats
void game::renderBar()
{
    this->window->draw(botBar.stats);
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
                tekst5text = "You have increased your\n      bet by 10";
                p1.bet += 10;
                p1.money -= 10;
                std::cout << "Bet: " << p1.bet << "\nCash: " << p1.money << std::endl;
            }
            if (coin20Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 20) {
                std::cout << "Zwiekszono bet o 20\n";
                tekst5text = "You have increased your\n      bet by 20";
                p1.bet += 20;
                p1.money -= 20;
            }
            if (coin50Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 50) {
                std::cout << "Zwiekszono bet o 50\n";
                tekst5text = "You have increased your\n      bet by 50";
                p1.bet += 50;
                p1.money -= 50;
            }
            if (coin100Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 100) {
                std::cout << "Zwiekszono bet o 100\n";
                tekst5text = "You have increased your\n      bet by 100";
                p1.bet += 100;
                p1.money -= 100;
            }
            if (coin200Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 200) {
                std::cout << "Zwiekszono bet o 200\n";
                tekst5text = "You have increased your\n      bet by 200";
                p1.bet += 200;
                p1.money -= 200;
            }
            if (coin500Sprite.getGlobalBounds().contains(this->mousePosView) && p1.money >= 500) {
                std::cout << "Zwiekszono bet o 500\n";
                tekst5text = "You have increased your\n      bet by 500";
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
                tekst5text = "You have reduced your\n     bet by 10";
                p1.bet -= 10;
                p1.money += 10;
                std::cout << "Bet: " << p1.bet << "\n Cash: " << p1.money;
            }
            if (coin20Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 20) {
                std::cout << "Zmniejszono bet o 20\n";
                tekst5text = "You have reduced your\n     bet by 20";
                p1.bet -= 20;
                p1.money += 20;
            }
            if (coin50Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 50) {
                std::cout << "Zmniejszono bet o 50\n";
                tekst5text = "You have reduced your\n     bet by 50";
                p1.bet -= 50;
                p1.money += 50;
            }
            if (coin100Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 100) {
                std::cout << "Zmniejszono bet o 100\n";
                tekst5text = "You have reduced your\n     bet by 100";
                p1.bet -= 100;
                p1.money += 100;
            }
            if (coin200Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 200) {
                std::cout << "Zmniejszono bet o 200\n";
                tekst5text = "You have reduced your\n     bet by 200";
                p1.bet -= 200;
                p1.money += 200;
            }
            if (coin500Sprite.getGlobalBounds().contains(this->mousePosView) && p1.bet >= 500) {
                std::cout << "Zmniejszono bet o 500\n";
                tekst5text = "You have reduced your\n     bet by 500";
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
    // Przypisanie pozycji pól do obstawiania
    sf::Vector2f redFieldPosition(600, 420);
    sf::Vector2f blackFieldPosition(670, 420);
    sf::Vector2f range1to12FieldPosition(740, 420);
    sf::Vector2f range13to24FieldPosition(810, 420);
    sf::Vector2f range25to36FieldPosition(880, 420);

    // Pobranie informacji o zdarzeniu
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld2 == false)
        {
            this->mouseHeld2 = true;
            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu sto³u
            for (int i = 0; i < TableSize; ++i)
            {
                if (tableFields[i].shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    std::cout << "Wybrano liczbe: " << i + 1 << "\n";
                    betNumbers.push_back(i + 1); 
                    tableFields[i].shape.setOutlineColor(sf::Color::Green);
                    betTypes.push_back(BetType("Number", 36));
                    for (auto a : betNumbers) {
                        std::cout << a << " \n";
                    }
                    break;
                }
                
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu czerwonym
            if (redField.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "Wybrano czerwone\n";
                betTypes.push_back(BetType("Red", 2));
                for (int i = 0; i < TableSize; ++i)
                {
                    if (tableFields[i].shape.getFillColor() == sf::Color::Red) {
                        tableFields[i].shape.setOutlineColor(sf::Color::Green);
                        betNumbers.push_back(i + 1);
                    }
                }
                for (auto a : betNumbers) {
                    std::cout << a << " \n";
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu czarnym
            if (blackField.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "Wybrano czarne\n";
                betTypes.push_back(BetType("Black", 2));
                for (int i = 0; i < TableSize; ++i)
                {
                    if (tableFields[i].shape.getOutlineColor() == sf::Color::Green)
                        break; 
                    if (tableFields[i].shape.getFillColor() == sf::Color::Black) {
                        tableFields[i].shape.setOutlineColor(sf::Color::Green);
                        betNumbers.push_back(i + 1);
                    }
                    
                }
                for (auto a : betNumbers) {
                    std::cout << a << " ";
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 1-12
            if (range1to12Field.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "Wybrano zakres liczb 1-12\n";
                betTypes.push_back(BetType("1-12", 3));
                for (int i = 0; i < 12; ++i)
                {
                    if (tableFields[i].shape.getOutlineColor() == sf::Color::Green)
                        break;
                    tableFields[i].shape.setOutlineColor(sf::Color::Green);
                    betNumbers.push_back(i + 1);
                }
                for (auto a : betNumbers) {
                    std::cout << a << " ";
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 13-24
            if (range13to24Field.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "Wybrano zakres liczb 13-24\n";
                betTypes.push_back(BetType("13-24", 3));
                for (int i = 12; i < 24; ++i)
                {
                    if (tableFields[i].shape.getOutlineColor() == sf::Color::Green)
                        break;
                    tableFields[i].shape.setOutlineColor(sf::Color::Green);
                    betNumbers.push_back(i + 1);
                }
                for (auto a : betNumbers) {
                    std::cout << a << " ";
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 25-36
            if (range25to36Field.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "Wybrano zakres liczb 25-36\n";
                betTypes.push_back(BetType("25-36", 3));
                for (int i = 24; i < 36; ++i)
                {
                    if (tableFields[i].shape.getOutlineColor() == sf::Color::Green)
                        break;
                    tableFields[i].shape.setOutlineColor(sf::Color::Green);
                    betNumbers.push_back(i + 1);
                }
                for (auto a : betNumbers) {
                    std::cout << a << " ";
                }
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (this->mouseHeld2 == false)
        {
            this->mouseHeld2 = true;
            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu sto³u
            for (int i = 0; i < TableSize; ++i)
            {
                if (tableFields[i].shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    if (!betTypes.empty())
                        betTypes.pop_back();
                    else
                        std::cout << "betTypes is empty\n";
                    std::cout << "Odznaczono liczbe: " << i + 1 << "\n";
                    tableFields[i].shape.setOutlineColor(sf::Color::Black);
                    for (int j = 0; j < betNumbers.size(); j++)
                    {
                        if(betNumbers[j] == i+1)
                            betNumbers.erase(betNumbers.begin() + j);
                    }
                    //break;
                }
            }
            for (auto a : betNumbers) {
                std::cout << a << " ";
            }
            for (int i = 0; i < betTypes.size(); i++) {
                std::cout << betTypes[i].name << "\n"; 
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu czerwonym
            if (redField.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!betTypes.empty())
                    betTypes.pop_back();
                else
                    std::cout << "betTypes is empty";
                std::cout << "Odznaczono czerwone\n";
                for (int i = 0; i < TableSize; ++i)
                {
                    if (tableFields[i].shape.getFillColor() == sf::Color::Red){
                        tableFields[i].shape.setOutlineColor(sf::Color::Black);
                        for (int j = 0; j < betNumbers.size(); j++)
                        {
                            if (betNumbers[j] == i + 1)
                                betNumbers.erase(betNumbers.begin() + j);
                        }
                    }
                }
                for (auto a : betNumbers) {
                    std::cout << a << " ";
                }

            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu czarnym
            if (blackField.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!betTypes.empty())
                    betTypes.pop_back();
                else
                    std::cout << "betTypes is empty";
                std::cout << "Odznaczono czarne\n";
                for (int i = 0; i < TableSize; ++i)
                {
                    if (tableFields[i].shape.getFillColor() == sf::Color::Black) {
                        tableFields[i].shape.setOutlineColor(sf::Color::Black);
                        betTypes.clear();
                        for (int j = 0; j < betNumbers.size(); j++)
                        {
                            if (betNumbers[j] == i + 1)
                                betNumbers.erase(betNumbers.begin() + j);
                        }
                    }
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 1-12
            if (range1to12Field.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!betTypes.empty())
                    betTypes.pop_back();
                else
                    std::cout << "betTypes is empty"; 
                std::cout << "Odznaczono zakres liczb 1-12\n";
                for (int i = 0; i < 12; ++i)
                {
                    tableFields[i].shape.setOutlineColor(sf::Color::Black);
                    for (int j = 0; j < betNumbers.size(); j++)
                    {
                        if (betNumbers[j] == i + 1)
                            betNumbers.erase(betNumbers.begin() + j);
                    }
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 13-24
            if (range13to24Field.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!betTypes.empty())
                    betTypes.pop_back();
                else
                    std::cout << "betTypes is empty";
                std::cout << "Odznaczono zakres liczb 13-24\n";
                for (int i = 12; i < 24; ++i)
                {
                    tableFields[i].shape.setOutlineColor(sf::Color::Black);
                    for (int j = 0; j < betNumbers.size(); j++)
                    {
                        if (betNumbers[j] == i + 1)
                            betNumbers.erase(betNumbers.begin() + j);
                    }
                }
            }

            // Sprawdzenie, czy klikniêcie nast¹pi³o na polu 25-36
            if (range25to36Field.stats.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (!betTypes.empty())
                    betTypes.pop_back();
                else
                    std::cout << "betTypes is empty";
                std::cout << "Odznaczono zakres liczb 25-36\n";
                for (int i = 24; i < 36; ++i)
                {
                    tableFields[i].shape.setOutlineColor(sf::Color::Black);
                    for (int j = 0; j < betNumbers.size(); j++)
                    {
                        if (betNumbers[j] == i + 1)
                            betNumbers.erase(betNumbers.begin() + j);
                    }
                }
            }
        }
    }
    else
    {
        this->mouseHeld2 = false;
    }

    // Rysowanie sto³u z cyframi
    for (int i = 0; i < TableSize; ++i)
    {
        this->window->draw(tableFields[i].shape);
        this->window->draw(tableFields[i].numberText);
        //tableFields[i].shape.setOutlineColor(IsWinningNumber(i + 1, 1) ? sf::Color::Green : sf::Color::Black);
    }

    // Rysowanie pól do obstawiania
    redField = UImodel(redFieldPosition.x, redFieldPosition.y, 50.f, 50.f);
    redField.stats.setFillColor(sf::Color::Red);
    this->window->draw(redField.stats);

    blackField = UImodel(blackFieldPosition.x, blackFieldPosition.y, 50.f, 50.f);
    blackField.stats.setFillColor(sf::Color::Black);
    this->window->draw(blackField.stats);

    range1to12Field = UImodel(range1to12FieldPosition.x, range1to12FieldPosition.y, 50.f, 50.f);
    range1to12Field.stats.setFillColor(sf::Color::White);
    range1to12Field.stats.setOutlineColor(sf::Color::Black);
    range1to12Field.stats.setOutlineThickness(1.0f);
    this->window->draw(range1to12Field.stats);

    range13to24Field = UImodel(range13to24FieldPosition.x, range13to24FieldPosition.y, 50.f, 50.f);
    range13to24Field.stats.setFillColor(sf::Color::White);
    range13to24Field.stats.setOutlineColor(sf::Color::Black);
    range13to24Field.stats.setOutlineThickness(1.0f);
    this->window->draw(range13to24Field.stats);

    range25to36Field = UImodel(range25to36FieldPosition.x, range25to36FieldPosition.y, 50.f, 50.f);
    range25to36Field.stats.setFillColor(sf::Color::White);
    range25to36Field.stats.setOutlineColor(sf::Color::Black);
    range25to36Field.stats.setOutlineThickness(1.0f);
    this->window->draw(range25to36Field.stats);
}

void game::bet()
{
    int winAmount = 0;
    this->initRandom();
    winAmount = p1.bet;
    p1.bet = 0;

    if (betTypes[0].name == "Red" && std::find(czerwone.begin(), czerwone.end(), randomNum) != czerwone.end())
    {
        std::cout << "Wybrales czerwone";
        winAmount = winAmount * 2;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        betNumbers.clear();
        betTypes.clear();
    }
    else if (betTypes[0].name == "Black" && std::find(czarne.begin(), czarne.end(), randomNum) != czarne.end())
    {
        std::cout << "Wybrales czarne";
        winAmount = winAmount * 2;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        betNumbers.clear();
        betTypes.clear();
    }
    else if (betTypes[0].name == "Number")
    {
        std::cout << "Wybrales liczby\n";
        winAmount /= betNumbers.size();

        bool isWinningNumber = false;
        for (int number : betNumbers)
        {
            if (number == randomNum)
            {
                isWinningNumber = true;
                break;
            }
        }

        if (isWinningNumber)
        {
            winAmount = winAmount * 36;
            std::cout << "Wygrana: " << winAmount << "\n";
            p1.money += winAmount;
        }
        else
        {
            std::cout << "Przegrana\n";
        }

        betNumbers.clear();
        betTypes.clear();
    }
    for (int i = 0; i < TableSize; ++i)
    {
        tableFields[i].shape.setOutlineColor(sf::Color::Black);
    }
}

void game::wheelSpin()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && p1.bet > 0)
    {
        if(this->mouseHeld3 == false)
        {
            if (tekst4._text.getGlobalBounds().contains(mousePos.x, mousePos.y) && betNumbers.size() > 0)
            {
                std::sort(betNumbers.begin(), betNumbers.end());
                betNumbers.erase(std::unique(betNumbers.begin(), betNumbers.end()), betNumbers.end());
                this->mouseHeld3 = true;
                std::cout << "Wcisnieto przycisk SPIN\n";
                bet();
            }
        }
    }
    else
    {
        this->mouseHeld3 = false;
    }
    
    //bet; 
}