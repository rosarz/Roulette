#include <iostream>
#include "game.h"

int main()
{   
    //Initialize game engine 
    game game; 


    //Texture loader 
    sf::Texture texture; 
    if(!texture.loadFromFile("assets/tlo.png"))
    {
        return 0; 
    }

    sf::Sprite background; 
    background.setTexture(texture); 

    //Game loop 
    while (game.isRunning()) 
    {
        //Update
        game.update(); 

        //Render
        game.render(); 
        
        //Put up the background
        //window.draw(background);

        //Draw game
        
    }
    return 0; 
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
