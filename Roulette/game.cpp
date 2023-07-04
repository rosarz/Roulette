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

    if (!wheelTex2.loadFromFile("assets/wheel1.png"))
    {
        std::cout << "Error::initFonts()::Failed to wheel texture from game.cpp\n";
    }
    else
        std::cout << "Wheel texture loaded from game.cpp\n";

    wheel = sf::RectangleShape(sf::Vector2f(220, 205));
    wheel.setPosition(80.0f, 160.0f);
    wheel.setTexture(&wheelTex);
    wheel.setScale(1.7f, 1.5f);

    wheel2 = sf::RectangleShape(sf::Vector2f(220, 205));
    wheel2.setPosition(170.0f, 200.0f);
    wheel2.setTexture(&wheelTex2);
    wheel2.setScale(1.35f, 1.7f);

    Animation = animation(&wheelTex, sf::Vector2u(11, 1), time);

}

void game::initWheelSpin()
{
    
}

void game::rotateWheel()
{
    // Inicjalizacja generatora liczb pseudolosowych
    int random = 0;
    int randomStop;
    
    sf::Clock clock;
    rd;
    gen = std::mt19937(rd());
    dist = std::uniform_int_distribution<>(600, 1000);
    randomStop = dist(gen); 
 
    wheelTex.setSmooth(true);
    

    sf::IntRect newUvRect;
    newUvRect.left = 0; 
    newUvRect.top = 0;

    while (playPause == 1) {
        
        deltaTime = clock.restart().asSeconds();
        //std::cout << "Wykonanie animacji zakrecenia ruletki\n";
        Animation.update(row, deltaTime);
        wheel.setTextureRect(Animation.uvRect);
        //std::cout << "Left:" << wheel.getTextureRect().left << "Top:" << wheel.getTextureRect().top << std::endl;
        this->window->draw(this->wheel);
        this->window->display();
        Animation.update(0, deltaTime);
        
        if (random <= randomStop - 400)
            Animation.switchTime = 0.05f;

        if (random > randomStop - 401){
            //std::cout << "KOLO ZWALNIA";
            Animation.switchTime += 0.001;
        }

        random++;
        //std::cout << random;
        if (random > randomStop) {
            playPause = 0;
            newUvRect.left = wheel.getTextureRect().left; 
            newUvRect.top = wheel.getTextureRect().top; 
        }
    }
    if (playPause == 0)
    {
        
        wheel.setTextureRect(Animation.uvRect);
        this->window->draw(this->wheel);
    }
    
}

void game::renderWheel()
{
    Animation.update(row, deltaTime);
    wheel.setTextureRect(Animation.uvRect);
    this->window->draw(this->wheel);
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
tekst6(30, sf::Color::Color(45, 147, 108), "RANKING", 1040.f, 20.f),
tekst7(90, sf::Color::Color(45, 147, 108), "ROULETTE", 320.f, 210.f),
tekst8(30, sf::Color::Color(45, 147, 108), "Resolution: 720x1280\n    Max FPS: 144\n\n  Build with SFML", 370.f, 90.f),
tekst9(30, sf::Color::Color(45, 147, 108), "Made by", 570.f, 580.f),
tekst10(30, sf::Color::Color(45, 147, 108), "Filip Soltysik", 460.f, 620.f),
tekst11(30, sf::Color::Color(45, 147, 108), "Input your nickname\n", 500.f, 290.f),
tekst12(30, sf::Color::Color(45, 147, 108), "SAVE", 585.f, 460.f),
tekst13(30, sf::Color::Color(45, 147, 108), "ss4.str()", 70.0f, 500.f),
tekst14(30, sf::Color::Color(45, 147, 108), "LOAD", 400.f, 460.f),
tekst15(30, sf::Color::Color(45, 147, 108), "DELETE", 770.f, 460.f),
tekst16(30, sf::Color::Color(45, 147, 108), "ss5.str()", 20.f, 20.f)
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
    this->initWheelSpin();
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
        case sf::Event::TextEntered:
            if (this->eve.text.unicode < 128) {
                char character = static_cast<char>(this->eve.text.unicode);
                p1.nickname += character;
                std::cout << "ASCII character typed: " << character << std::endl;
                std::cout << p1.nickname; 
            }
        //case sf::Event::MouseButtonPressed:
        //    if (eve.type == sf::Event::MouseButtonPressed)
        //    {
        //        if (eve.mouseButton.button == sf::Mouse::Left)
        //        {
        //            std::cout << "Wcisnieto lewy przycisk myszy" << std::endl;
        //            rotateWheel();
        //        }
        //    }
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
    std::stringstream ss4;
    std::stringstream ss5;
    
    ss << "Cash:" << p1.money;
    ss2 << "Bet:" << p1.bet;
    ss3 << tekst5text;
    ss4 << winText; 
    ss5 << rankText;

    tekst1._text.setString(ss.str());
    tekst2._text.setString(ss2.str());
    tekst5._text.setString(ss3.str());
    tekst13._text.setString(ss4.str());
    tekst16._text.setString(ss5.str());
    

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
    //target.draw(tekst6._text);
    target.draw(tekst13._text);
    target.draw(tekst16._text);
    p1.loadMaxWin("maxWin.bin", maxwin);
    rankText = "Biggest win is: " + std::to_string(p1.maxWin);
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
            settings = false; 
            render2();
            std::cout << "1\n";
            
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
    if (io == true && settings == true) {
    this->window->clear();

    //Draw the game
    this->renderBackground();
    this->renderBar();
    this->renderText(*this->window);
    this->colorChange();
    this->updateText();
    this->renderCoins();
    //this->renderWheel();
    this->rouletteFunc();
    this->wheelSpin();
    this->rotateWheel();
    
    //Animation = animation(&wheelTex, sf::Vector2u(11, 1), time);
    //wheel.setTextureRect(Animation.uvRect);
    //this->window->draw(this->wheel);
    

    this->window->display();
    }
}

void game::render2()
{
    if (io == false && settings == true)
    {
        this->window->clear();

        this->renderBackground();
        this->renderMenu();
        this->menuParts();

        this->window->display();
    }
    if (settings == false)
    {
        this->window->clear();

        this->renderBackground();
        this->settingsInfo();

        this->window->display();
    }
}

void game::settingsInfo()
{
    std::stringstream ss;
    ss << " Nickname:\n   " << p1.nickname;
    tekst11._text.setString(ss.str());
    
    //this->window->draw(tekst6._text);
    this->window->draw(tekst8._text);
    this->window->draw(tekst9._text);
    this->window->draw(tekst10._text);
    this->window->draw(tekst11._text);
    this->window->draw(tekst12._text);
    this->window->draw(tekst14._text);
    this->window->draw(tekst15._text);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) 
    {
        if(this->buttonHeld3 == false) //fix the multi-clicking in typing
        {
            buttonHeld3 = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                p1.nickname.pop_back();
                settings = true;
                std::cout << "0\n";
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace))
            {
                p1.nickname.pop_back();
                p1.nickname.pop_back();
            }
        }
    }
    else
    {
        this->buttonHeld3 = false;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld4 == false)
        {
            mouseHeld4 = true;
            if (tekst12._text.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                //save(p1.nickname);
                p1.saveData();
                std::cout << "Zapisano gre\n";
            }
            if (tekst14._text.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                p1.loadData();
                std::cout << p1.nickname << " " << p1.maxWin << std::endl;
                //p1.loadMaxWin("maxWin.bin", maxwin);
                //rankText = "Biggest win is: " + std::to_string(maxwin);
                //std::cout << p1.last_win; 
                
            }
            if (tekst15._text.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                p1.deleteSaveFile();
            }
            if (tekst6._text.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                
            }
        }
    }
    else
    {
        this->mouseHeld4 = false;
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
                betTypes.push_back(BetType("range1to12", 3));
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
                betTypes.push_back(BetType("range13to24", 3));
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
                betTypes.push_back(BetType("range25to36", 3));
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
    this->initRandom();
    winAmount = p1.bet;
    p1.bet = 0;

    if (betTypes[0].name == "Red" && std::find(czerwone.begin(), czerwone.end(), randomNum) != czerwone.end())
    {
        std::cout << "Wybrales czerwone";
        winAmount = winAmount * 2;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        p1.last_win += winAmount; 
        maxWin();
        winText = "Win number: " + std::to_string(randomNum);
        tekst5text = "     You won: " + std::to_string(winAmount);
        betNumbers.clear();
        betTypes.clear();
        winAmount = 0; 
    }
    else if (betTypes[0].name == "Black" && std::find(czarne.begin(), czarne.end(), randomNum) != czarne.end())
    {
        std::cout << "Wybrales czarne";
        winAmount = winAmount * 2;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        p1.last_win += winAmount;
        maxWin();
        winText = "Win number: " + std::to_string(randomNum);
        tekst5text = "     You won: " + std::to_string(winAmount);
        betNumbers.clear();
        betTypes.clear();
        winAmount = 0;
    }
    else if (betTypes[0].name == "range1to12" && std::find(range1to12.begin(), range1to12.end(), randomNum) != range1to12.end())
    {
        std::cout << "Wybrales zakres 1-12";
        winAmount = winAmount * 3;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        p1.last_win += winAmount;
        maxWin();
        winText = "Win number: " + std::to_string(randomNum);
        tekst5text = "     You won: " + std::to_string(winAmount);
        betNumbers.clear();
        betTypes.clear();
        winAmount = 0;
    }
    else if (betTypes[0].name == "range13to24" && std::find(range13to24.begin(), range13to24.end(), randomNum) != range13to24.end())
    {
        std::cout << "Wybrales zakres 13-24";
        winAmount = winAmount * 3;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        p1.last_win += winAmount;
        maxWin();
        winText = "Win number: " + std::to_string(randomNum);
        tekst5text = "     You won: " + std::to_string(winAmount);
        betNumbers.clear();
        betTypes.clear();
        winAmount = 0;
    }
    else if (betTypes[0].name == "range25to36" && std::find(range25to36.begin(), range25to36.end(), randomNum) != range25to36.end())
    {
        std::cout << "Wybrales zakres 25-36";
        winAmount = winAmount * 3;
        std::cout << winAmount << "\n";
        p1.money += winAmount;
        p1.last_win += winAmount;
        maxWin();
        winText = "Win number: " + std::to_string(randomNum);
        tekst5text = "     You won: " + std::to_string(winAmount);
        betNumbers.clear();
        betTypes.clear();
        winAmount = 0;
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
            p1.last_win += winAmount;
            maxWin(); 
            std::cout << "Wygrana: " << winAmount << "\n";
            tekst5text = "    You won: " + std::to_string(winAmount);
            winText = "Win number: " + std::to_string(randomNum); 
            p1.money += winAmount;
            winAmount = 0;
        }
        else
        {
            tekst5text = "    You lost :(";
            winText = "Win number: " + std::to_string(randomNum);
            std::cout << "Przegrana\n";
        }
    }
    else
    {
        tekst5text = "    You lost :(";
        winText = "Win number: " + std::to_string(randomNum);
        std::cout << "Przegrana\n";
    }

    for (int i = 0; i < TableSize; ++i)
    {
        tableFields[i].shape.setOutlineColor(sf::Color::Black);
    }
    betNumbers.clear();
    betTypes.clear();
}

void game::wheelSpin()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && p1.bet > 0)
    {
        if(this->mouseHeld3 == false)
        {
            if (tekst4._text.getGlobalBounds().contains(mousePos.x, mousePos.y) && betNumbers.size() > 0)
            {
                playPause = 1; 
                this->rotateWheel();
                std::sort(betNumbers.begin(), betNumbers.end());
                betNumbers.erase(std::unique(betNumbers.begin(), betNumbers.end()), betNumbers.end());
                this->mouseHeld3 = true;
                std::cout << "Wcisnieto przycisk SPIN\n";
                bet();
                //Animation.update(row, deltaTime);
                //wheel.setTextureRect(Animation.uvRect);
                //this->window->draw(this->wheel);
            }
        }
    }
    else
    {
        this->mouseHeld3 = false;
    }
}

void game::maxWin()
{
    if (winAmount > p1.maxWin){
        p1.maxWin = 0; 
        p1.maxWin += winAmount;
        std::cout << "Nowy rekord: " + std::to_string(p1.maxWin);
        p1.saveMaxWin();
    }
}
