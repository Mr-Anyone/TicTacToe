#ifndef GAME_HPP 
#define GAME_HPP 

#include <vector> 
#include <array> 

enum BoardState{
    CROSS,
    CIRCLE,
    EMPTY
};

enum GameState{
    CROSS_WIN, 
    CIRCLE_WIN,
    TIE_GAME, 
    ON_GOING
};

enum Turn{
    CROSS_TURN,
    CIRCLE_TURN
}; 

typedef std::array<std::array<BoardState, 3>, 3> Board;



Board makeBoard();
void printBoard(const Board& board);
GameState getGameState(const Board& board);

#endif