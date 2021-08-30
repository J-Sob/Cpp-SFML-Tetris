#ifndef TETROMINO_H
#define TETROMINO_H

#include <Engine.h>


class Tetromino : public Engine
{
    public:
        Tetromino();
        virtual ~Tetromino();
        Tetromino(const Tetromino& other);
        Tetromino& operator=(const Tetromino& other);

    protected:

    private:
};

#endif // TETROMINO_H
