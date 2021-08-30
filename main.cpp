#include <iostream>
#include "GameGUI.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(500,500),"Tetris",sf::Style::Close);
    Game *myGame = new GameGUI(window);
    myGame->playGame(window);

    return 0;
}
