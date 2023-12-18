#include <iostream>
#include "game.hpp"

int main(){
    Board board = makeBoard();


    // cross start first
    Turn turn = Turn::CROSS_TURN;
    while(getGameState(board) == GameState::ON_GOING){
        printBoard(board);

        int row, col;
        std::cin >> row >> col;
        
        // putting stuff on the board
        if(turn == Turn::CIRCLE_TURN){
            board[row][col] = BoardState::CIRCLE;
        }else{
            board[row][col] = BoardState::CROSS;
        }

        
        // changing turn
        if(turn == Turn::CROSS_TURN){
            turn = Turn::CIRCLE_TURN;
        }else{
            turn = Turn::CROSS_TURN;
        }
    }

    return 0;
}
