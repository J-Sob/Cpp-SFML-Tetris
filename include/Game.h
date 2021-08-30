#ifndef GAME_H
#define GAME_H

#include <Engine.h>
#include <SFML/Graphics.hpp>

class Game : public Engine
{
    public:
        Game();
        virtual ~Game();
        Game(const Game& other) = delete;
        Game& operator=(const Game& other) = delete;

        void playGame(sf::RenderWindow &window);
        virtual void draw(sf::RenderWindow &window) = 0;
        void keyboardInput(sf::Keyboard::Key key);

    protected:

    private:
};

#endif // GAME_H
