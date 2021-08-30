#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include <Game.h>


class GameConsole : public Game
{
    public:
        GameConsole();
        virtual ~GameConsole();
        GameConsole(const GameConsole& other) = delete;
        GameConsole& operator=(const GameConsole& other) = delete;

        void draw();

    protected:

    private:
        char tile;
};

#endif // GAMECONSOLE_H
