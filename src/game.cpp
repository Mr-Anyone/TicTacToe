#include <iostream>
#include "game.hpp"

Board makeBoard(){
    Board board; 
    for(int i = 0 ; i<3; ++i){
        for(int j= 0;j<3; ++j){
            board[i][j] = BoardState::EMPTY;
        }
    }

    return board;
}

void printBoard(const Board& board){
    for(int i =0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            switch(board[i][j]){
                case BoardState::CIRCLE: 
                    std::cout << "O";
                    break; 
                case BoardState::CROSS: 
                    std::cout << "X";
                    break; 
                case BoardState::EMPTY:
                    std::cout << "-"; 
                    break;
            }

            if(j != 2){
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
}

bool didPlayerWin(const Board& board, BoardState state){
    // row
    for(int row = 0; row<3; ++row){
        if(board[row][0] == state && board[row][1] == state && board[row][2] == state){
            return true;
        }
    }
    // col
    for(int col = 0; col<3; ++col){
        if(board[0][col] == state && board[1][col] == state && board[2][col] == state){
            return true;
        }
    }
    //diagonal
    if(board[0][0] == state && board[1][1] == state && board[2][2] == state){
        return true;
    }

    if(board[0][2] == state && board[1][1] == state && board[2][0] == state){
        return true;
    }

    return false;
}

GameState getGameState(const Board& board){
    // is it a tie game?
    bool is_tie = true;
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            if(board [i][j] == BoardState::EMPTY){
                is_tie = false;
            }
        }
    }

    if(is_tie){
        return GameState::TIE_GAME;
    }
    
    // did someone win?
    if(didPlayerWin(board, BoardState::CIRCLE)){
        return CIRCLE_WIN;
    }

    if(didPlayerWin(board, BoardState::CROSS)){
        return CROSS_WIN;
    }

    return GameState::ON_GOING;
}