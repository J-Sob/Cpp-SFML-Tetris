#include "Engine.h"

Engine::Engine(int columns, int rows)
{
    this->boardColumns = columns;
    this->boardRows = rows;
    this->score = 0;
    this->GameOver = false;
    // dynamically creates board of given size
    this->board = new bool*[rows];
    for(int i = 0; i < boardRows; i++)
    {
        board[i] = new bool[boardColumns];
    }
    clearBoard();       // filling bool board with 0's
    tetro = newTetromino();
    upcomingTetro = newTetromino();
    srand(time(NULL));
}

Engine::~Engine()
{
    for(int i = 0; i < boardRows ; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

void Engine::checkBoard()
{
    for(int i = boardRows - 1; i >= 0; i--) // going through array starting from end (bottom of board)
    {
        int usedSlots = 0;
        for(int j = 0; j < boardColumns; j++)
        {
            if(board[i][j] == 1) usedSlots++;
        }
        if(usedSlots == boardColumns)   // if any row is full it gets cleared, stack gets lowered and score is updated
        {
            clearRow(i);
            addPoints();
            lowerRows(i);
        }
    }
}

Engine::Tetromino Engine::newTetromino()
{
    Tetromino tetro;
    Shape randomTetro = static_cast<Shape>(rand()%7);   // generating random shape
    tetro.rowPosition = 0;
    tetro.columnPosition = boardColumns / 2 - 2;

    switch (randomTetro)    // creating piece depending generated shape
    {
    case Shape::ISHAPE:
        tetro.tetroPosition[1][0] = 1;
        tetro.tetroPosition[1][1] = 1;
        tetro.tetroPosition[1][2] = 1;
        tetro.tetroPosition[1][3] = 1;
        break;
    case Shape::TSHAPE:
        tetro.tetroPosition[0][1] = 1;
        tetro.tetroPosition[0][2] = 1;
        tetro.tetroPosition[0][3] = 1;
        tetro.tetroPosition[1][2] = 1;
        break;
    case Shape::RECTSHAPE:
        tetro.tetroPosition[0][1] = 1;
        tetro.tetroPosition[0][2] = 1;
        tetro.tetroPosition[1][1] = 1;
        tetro.tetroPosition[1][2] = 1;
        break;
    case Shape::LSHAPE:
        tetro.tetroPosition[1][1] = 1;
        tetro.tetroPosition[1][2] = 1;
        tetro.tetroPosition[0][3] = 1;
        tetro.tetroPosition[1][3] = 1;
        break;
    case Shape::JSHAPE:
        tetro.tetroPosition[1][1] = 1;
        tetro.tetroPosition[1][2] = 1;
        tetro.tetroPosition[1][3] = 1;
        tetro.tetroPosition[0][1] = 1;
        break;
    case Shape::SSHAPE:
        tetro.tetroPosition[0][2] = 1;
        tetro.tetroPosition[0][3] = 1;
        tetro.tetroPosition[1][1] = 1;
        tetro.tetroPosition[1][2] = 1;
        break;
    case Shape::ZSHAPE:
        tetro.tetroPosition[0][1] = 1;
        tetro.tetroPosition[0][2] = 1;
        tetro.tetroPosition[1][2] = 1;
        tetro.tetroPosition[1][3] = 1;
        break;
    }
        return tetro;
}

void Engine::moveTetromino(Direction dir)
{
    switch(dir)
    {
    case Direction::DOWN:
        if(!getGameOver()){
            lowerTetromino();
        }
        break;
    case Direction::LEFT:
        tetro.columnPosition--;     // moving piece
        if(leftCollision() == true || stackCollision() == true)
        {
            tetro.columnPosition++;     // if piece collides with either wall or stack move is reverted
        }
        break;
    case Direction::RIGHT:
        tetro.columnPosition++;     // moving piece
        if(rightCollision() == true || stackCollision() == true)
        {
            tetro.columnPosition--;     // if piece collides with either wall or stack move is reverted
        }
        break;
    }
}

void Engine::lowerTetromino()
{
    tetro.rowPosition++;        // lowering tetro
    if(bottomCollision() == true || stackCollision() == true)   // if piece collides with either stack or bottom wall
    {
        tetro.rowPosition--;    // move gets reverted
        addToStack();       // piece is added to the stack
        tetro = upcomingTetro;      // current piece becomes the upcoming one
        upcomingTetro = newTetromino();     // generating new upcoming piece
        if(stackCollision())        // checking if new piece collides with stack, if yes game is over
            this->GameOver = true;
    }
}

void Engine::rotateTetromino()
{
    bool temp[4][4] = {false};      // creating temporary array and copying falling piece position into it
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetro.tetroPosition[i][j] == true)
            {
                temp[i][j] = tetro.tetroPosition[i][j];
            }
        }
    }
    int initialColumn = tetro.columnPosition;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            tetro.tetroPosition[i][j] = temp[3 - j][i];     // rotating piece
        }
    }

    while(leftCollision())      // if piece collides with any wall it gets moved opposite way
    {
        tetro.columnPosition += 1;
    }

    while(rightCollision())
    {
        tetro.columnPosition -= 1;
    }

    if(stackCollision())        // if piece collides with stack move gets reverted
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                tetro.tetroPosition[i][j] = temp[i][j];
            }
        }
        tetro.columnPosition = initialColumn;
        return;
    }
}

void Engine::lowerRows(int index)
{
    for(int i = index - 1; i > 0; i--)
    {
        for(int j = 0; j < boardColumns; j++)
        {
            board[i+1][j] = board[i][j];
            board[i][j] = board[i-1][j];
        }
    }
}

void Engine::addToStack()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetro.tetroPosition[i][j] == true)
            {
                int realColumnPos = tetro.columnPosition + j;   // calculating position of piece on main board
                int realRowPos = tetro.rowPosition + i;
                board[realRowPos][realColumnPos] = true;
            }
        }
    }
}

void Engine::clearRow(int index)
{
    for(int i = 0; i < boardColumns; i++)
    {
        board[index][i] = 0;
    }
}

void Engine::clearBoard()
{
    for(int i =0; i < boardRows; i++)
    {
        for(int j = 0; j < boardColumns; j++)
        {
            board[i][j] = 0;
        }
    }
}

bool Engine::stackCollision()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetro.tetroPosition[i][j] == true)
            {
                int realColumnPos = tetro.columnPosition + j;
                int realRowPos = tetro.rowPosition + i;
                if(board[realRowPos][realColumnPos] == true)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


bool Engine::bottomCollision()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetro.tetroPosition[i][j] == true)
            {
                int realRowPos = tetro.rowPosition + i;
                if(realRowPos == boardRows)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Engine::leftCollision()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetro.tetroPosition[i][j] == true)
            {
                int realColumnPos = tetro.columnPosition + j;
                if(realColumnPos < 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Engine::rightCollision()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(tetro.tetroPosition[i][j] == true)
            {
                int realColumnPos = tetro.columnPosition + j;
                if(realColumnPos >= boardColumns)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Engine::addPoints()        // very simple points system, definitely something to upgrade
{
    this->score = score + 100;
}

void Engine::restartGame()
{
    clearBoard();
    this->score = 0;
    this->GameOver = false;
}


int Engine::getScore()
{
    return this->score;
}

bool Engine::getGameOver()
{
    return this->GameOver;
}

int Engine::getBoardRows()
{
    return this->boardRows;
}

int Engine::getBoardColumns()
{
    return this->boardColumns;
}

bool Engine::getTileStatus(int i, int j)
{
    return board[i][j];
}

int Engine::getTetroColumnPos()
{
    return this->tetro.columnPosition;
}

int Engine::getTetroRowPos()
{
    return this->tetro.rowPosition;
}

bool Engine::getTetroStatus(int i, int j)
{
    return this->tetro.tetroPosition[i][j];
}

bool Engine::getUpcomingTetroStatus(int i, int j)
{
    return this->upcomingTetro.tetroPosition[i][j];
}

