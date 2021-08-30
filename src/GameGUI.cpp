#include "GameGUI.h"

GameGUI::GameGUI() : Game()
{
    //ctor
}

GameGUI::GameGUI(sf::RenderWindow &window)
{
    this->tileWidth = window.getSize().y / getBoardRows();
    this->tileHeight = tileWidth;

    this->fallingTile = sf::Color(0, 163, 14);
    this->stackTile = sf::Color(0, 50, 163);
    this->backgroundColor = sf::Color(224, 224, 224);
}

GameGUI::~GameGUI()
{
    //dtor
}

void GameGUI::draw(sf::RenderWindow &window)
{
    window.clear(sf::Color::White);

    drawStack(window);
    drawFallingTetro(window);
    drawUpcomingTetro(window);
    drawText(window);
    window.display();
}

void GameGUI::drawStack(sf::RenderWindow &window)
{
    for(int i = 0; i < getBoardRows(); i++)
    {
        for(int j = 0; j < getBoardColumns(); j++)
        {
            sf::RectangleShape tile(sf::Vector2f(tileWidth,tileHeight));
            if(getTileStatus(i,j) == true)
            {
                tile.setFillColor(stackTile);
            }
            else
            {
                tile.setFillColor(backgroundColor);
            }
            tile.setOutlineColor(sf::Color::Black);
            tile.setOutlineThickness(1.f);
            tile.move(sf::Vector2f(j * tileWidth, i * tileHeight));     // moving each rectangle by the size of the cell so they don't interfere with eachother
            window.draw(tile);
        }
    }
}

void GameGUI::drawFallingTetro(sf::RenderWindow &window)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(getTetroStatus(i,j) == true)
            {
                int realColumnPos = getTetroColumnPos() + j;
                int realRowPos = getTetroRowPos() + i;
                sf::RectangleShape tile(sf::Vector2f(tileWidth,tileHeight));
                tile.setFillColor(fallingTile);
                tile.setOutlineColor(sf::Color::Black);
                tile.setOutlineThickness(1.f);
                tile.move(sf::Vector2f(realColumnPos * tileWidth, realRowPos * tileHeight));
                window.draw(tile);
            }
        }
    }
}

void GameGUI::drawUpcomingTetro(sf::RenderWindow &window)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            sf::RectangleShape tile(sf::Vector2f(tileWidth,tileHeight));
            if(getUpcomingTetroStatus(i,j) == true)
            {

                tile.setFillColor(fallingTile);

            }
            else
            {
                tile.setFillColor(backgroundColor);
            }
            tile.setOutlineColor(sf::Color::Black);
            tile.setOutlineThickness(1.f);
            tile.move(sf::Vector2f(j * tileWidth + (window.getSize().x * 0.65), tileHeight * i ));
            window.draw(tile);
        }
    }
}

void GameGUI::drawText(sf::RenderWindow &window)
{
    sf::Font myFont;
    myFont.loadFromFile("Bubblegum.ttf");
    sf::Text nextBlock("Next block", myFont, 30);
    sf::Text myScore("Your score", myFont, 30);
    sf::Text points(std::to_string(getScore()), myFont, 50);
    sf::Text GameOver("Game over!", myFont, 30);
    sf::Text Restart("Press Space to restart", myFont, 15);

    nextBlock.setFillColor(sf::Color::Black);
    nextBlock.move(window.getSize().x * 0.6, window.getSize().y * 0.2);
    window.draw(nextBlock);

    myScore.setFillColor(sf::Color::Black);
    myScore.move(window.getSize().x * 0.6, window.getSize().y * 0.5);
    window.draw(myScore);

    points.setFillColor(sf::Color::Black);
    points.move(window.getSize().x * 0.6, window.getSize().y * 0.4);
    window.draw(points);


    if(getGameOver())
    {
        GameOver.setFillColor(sf::Color::Black);
        GameOver.move(window.getSize().x * 0.6, window.getSize().y * 0.7);
        window.draw(GameOver);

        Restart.setFillColor(sf::Color::Black);
        Restart.move(window.getSize().x * 0.6, window.getSize().y * 0.8);
        window.draw(Restart);
    }

}

