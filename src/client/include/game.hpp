#ifndef GAME_HPP 
#define GAME_HPP 

#include "shared.hpp"

Board makeBoard();
void printBoard(const Board& board);
GameState getGameState(const Board& board);

#endif