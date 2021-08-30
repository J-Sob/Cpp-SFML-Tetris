#include "Game.h"

Game::Game() : Engine()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::playGame(sf::RenderWindow &window)
{
    sf::Clock clock;
    while(window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ))
            {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                keyboardInput(sf::Keyboard::Left);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                keyboardInput(sf::Keyboard::Right);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                keyboardInput(sf::Keyboard::Down);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                keyboardInput(sf::Keyboard::Up);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                keyboardInput(sf::Keyboard::Space);
            }
        }
        if(elapsed.asSeconds() >= 0.6 && !getGameOver())
        {
            lowerTetromino();
            clock.restart();
        }
        checkBoard();
        draw(window);
    }
}

void Game::keyboardInput(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        moveTetromino(Direction::LEFT);
        break;
    case sf::Keyboard::Right:
        moveTetromino(Direction::RIGHT);
        break;
    case sf::Keyboard::Down:
        moveTetromino(Direction::DOWN);
        break;
    case sf::Keyboard::Up:
        rotateTetromino();
        break;
    case sf::Keyboard::Space:
        if(getGameOver())
        {
            restartGame();
        }
        break;
    default:
        break;
    }
}
