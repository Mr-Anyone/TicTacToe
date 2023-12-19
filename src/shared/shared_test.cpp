#include "shared.hpp"
#include<SFML/Network.hpp> 
#include <iostream>

bool casting_test(){
    NetworkPacket data;
    // creating data to be sent
    Board board; 
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            board[i][j] = BoardState::CIRCLE;
        }
    }
    data.board = board; 
    data.turn = Turn::CIRCLE_TURN; 
    data.player = Player::CIRCLE;

    sf::Packet packet;
    packet << data;
    NetworkPacket new_data; 
    packet >> new_data; 

    if(new_data.turn != data.turn){
        return false;
    }
    if(new_data.player != data.player){
        return false;
    }
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            if(new_data.board[i][j] != data.board[i][j]){
                return false;
            }
        }
    }

    return true;
}

bool casting_test_2(){
    sf::Packet packet; 
    UpdatePositionPacket data; 
    data.x = 100; 
    data.y =200;

    packet << data; 
    UpdatePositionPacket new_data; 
    packet >> new_data; 

    if(new_data.x == data.x || new_data.y == data.y){
        return true;
    }

    return false;
}

int main(){
    if(!casting_test()){
        std::cout << "Casting Test Failed" << std::endl;
        return -1;
    }

    if(!casting_test_2()){
        std::cout << "Casting Test 2 Failed" << std::endl; 
        return -1;
    }
    std::cout << "Casting Test Passed" << std::endl;

    return 0; // successful test
}