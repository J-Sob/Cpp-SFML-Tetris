#ifndef ENGINE_H
#define ENGINE_H

#include <cstdlib>
#include <ctime>

class Engine
{
    protected:
        Engine(int columns = 10, int rows = 20);    // constructor with default parameters
        virtual ~Engine();
        Engine(const Engine& other) = delete;       // preventing unwanted usage
        Engine& operator=(const Engine& other) = delete;    // preventing unwanted usage

        enum class Direction {      // enum used in moving piece
            RIGHT,
            LEFT,
            DOWN,
        };
        // standard getters
        int getScore();
        int getBoardRows();
        int getBoardColumns();
        bool getGameOver();
        int getTetroColumnPos();
        int getTetroRowPos();
        bool getTetroStatus(int i, int j);
        bool getUpcomingTetroStatus(int i, int j);
        bool getTileStatus(int i, int j);

        void checkBoard();      // method checks if any row has been filled
        void moveTetromino(Direction dir);      // moving falling piece on game board
        void lowerTetromino();      // lowering falling piece one row at a time
        void rotateTetromino();     // rotating falling piece
        void restartGame();

    private:
        enum class Shape {      // standard Tetris shapes
            ISHAPE,
            TSHAPE,
            RECTSHAPE,
            LSHAPE,
            JSHAPE,
            SSHAPE,
            ZSHAPE,
        };

        struct Tetromino{       // private structure containing information about falling piece
            int rowPosition;    // row position independent of main game board
            int columnPosition;     // column position independent of main game board
            bool tetroPosition [4][4] = {false};    // small array containing shape of the piece
        };

        bool GameOver;
        int boardColumns;
        int boardRows;
        bool **board;
        int score;
        Tetromino newTetromino();       // method creates random tetromino
        Tetromino tetro;        // currently falling piece
        Tetromino upcomingTetro;        // next piece in line
        void addPoints();    // simply adding points

        // methods to check if falling piece collides with either walls or stack
        bool stackCollision();
        bool bottomCollision();
        bool leftCollision();
        bool rightCollision();

        void addToStack();      // adding fallen piece to stack
        void lowerRows(int index);      // lowering stack from given index
        void clearRow(int index);       // clearing row of given index
        void clearBoard();      // clearing whole board
};

#endif // ENGINE_H
