#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#include "shared.hpp"

constexpr long long TICK_RATE_MS = 500;

void send_packet(sf::TcpSocket& socket, NetworkPacket& data){
    sf::Packet packet;
    packet << data;

    if(socket.send(packet) != sf::Socket::Status::Done){
        std::cout << "cannot send player packet" << std::endl; 
        exit(-1);
    }
}

int main(){
    sf::TcpListener listener;
    NetworkPacket global_state = makeNewNetworkPacket();
    global_state.board[0][0] = BoardState::CIRCLE;


    if (listener.listen(10000) != sf::Socket::Status::Done){
        std::cout << "I cannot be binded to address" << std::endl;
        return -1;
    }
    // waiting for players to connect
    std::cout << "setup listener! Listener has been setup!" << std::endl;
    sf::TcpSocket player1; 
    sf::TcpSocket player2; 

    if(listener.accept(player1) != sf::Socket::Status::Done){
        std::cout << "cannot accpet listener" << std::endl; 
        return -1;
    }
    
    global_state.player = Player::CIRCLE;
    send_packet(player1, global_state);
  

    if(listener.accept(player2) != sf::Socket::Status::Done){
        std::cout << "cannot accpet listener" << std::endl; 
        return -1;
    }

    global_state.player = Player::CROSS;
    send_packet(player2, global_state);


    // enter loop
    while(true){
        global_state.player = Player::CROSS;
        send_packet(player2, global_state);
        
        global_state.player = Player::CIRCLE;
        send_packet(player1, global_state);

        // waiting for packet based on turn
        if(global_state.turn == Turn::CROSS_TURN){
            // wait for cross packet
            sf::Packet packet;
            if(player2.receive(packet) != sf::Socket::Status::Done){
                std::cout << "I don't have your packet" << std::endl; 
                exit(-1);
            }

            std::cout << "I got your packet" << std::endl;

            UpdatePositionPacket data; 
            packet >> data; 
            global_state.board[data.x][data.y] = BoardState::CROSS;
            global_state.turn = Turn::CIRCLE_TURN;
           // sending packet every TICK_RATE_MS
            std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MS));    
            continue;
        }

        if(global_state.turn == Turn::CIRCLE_TURN){
            sf::Packet packet; 
            
            if(player1.receive(packet) != sf::Socket::Status::Done){
                std::cout << "I don't got your packet" << std::endl; 
                exit(-1);
            }
            
            UpdatePositionPacket data; 
            packet >> data; 
            global_state.board[data.x][data.y] = BoardState::CIRCLE;
            global_state.turn = Turn::CROSS_TURN;

           // sending packet every TICK_RATE_MS
            std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MS));    
            continue;
        }

    }
    return 0;
}