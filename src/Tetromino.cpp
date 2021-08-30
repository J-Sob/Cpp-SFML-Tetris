#include "Tetromino.h"

Tetromino::Tetromino()
{
    //ctor
}

Tetromino::~Tetromino()
{
    //dtor
}

Tetromino::Tetromino(const Tetromino& other)
{
    //copy ctor
}

Tetromino& Tetromino::operator=(const Tetromino& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
