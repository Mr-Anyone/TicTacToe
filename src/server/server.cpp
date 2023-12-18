#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#include "shared.hpp"

constexpr long long TICK_RATE_MS = 500;

int main(){
    sf::TcpListener listener;
    NetworkPacket global_state = makeNewNetworkPacket();

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
    
    {
        sf::Packet packet;
        global_state.player = Player::CIRCLE;
        packet << global_state;

        if(player1.send(packet) != sf::Socket::Status::Done){
            std::cout << "cannot send player packet" << std::endl; 
            return -1;
        }
    }

    if(listener.accept(player2) != sf::Socket::Status::Done){
        std::cout << "cannot accpet listener" << std::endl; 
        return -1;
    }

    {
        sf::Packet packet;
        global_state.player = Player::CROSS;
        packet << global_state;
        
        if(player2.send(packet) != sf::Socket::Status::Done){
            std::cout << "cannot send player packet" << std::endl; 
            return -1;
        }
    }
    // enter loop
    while(true){
        std::cout << "I've looped" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(TICK_RATE_MS));    
    }
    return 0;
}