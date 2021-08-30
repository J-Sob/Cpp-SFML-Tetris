#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <Game.h>
#include <string>

class GameGUI : public Game
{
    public:
        GameGUI();
        GameGUI(sf::RenderWindow &window);
        virtual ~GameGUI();
        GameGUI(const GameGUI& other) = delete;
        GameGUI& operator=(const GameGUI& other) = delete;

        void draw(sf::RenderWindow &window);
        void drawStack(sf::RenderWindow &window);
        void drawUpcomingTetro(sf::RenderWindow &window);
        void drawFallingTetro(sf::RenderWindow &window);
        void drawText(sf::RenderWindow &window);
    protected:

    private:
        int tileWidth;
        int tileHeight;
        sf::Color fallingTile;
        sf::Color stackTile;
        sf::Color backgroundColor;
};

#endif // GAMEGUI_H
