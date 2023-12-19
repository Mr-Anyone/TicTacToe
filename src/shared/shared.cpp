#include <iostream> 
#include <SFML/Network.hpp>
#include "shared.hpp"

sf::Packet& operator<< (sf::Packet& packet, const BoardState& state){
    packet << static_cast<int> (state); 
    return packet;
}

sf::Packet& operator >> (sf::Packet& packet, BoardState& state){
    int data;
    packet >> data;
    state = static_cast<BoardState> (data); 
    return packet;
}

sf::Packet& operator<< (sf::Packet& packet, const Turn& state){
    packet << static_cast<int> (state); 
    return packet;
}

sf::Packet& operator >> (sf::Packet& packet, Turn& state){
    int data;
    packet >> data;
    state = static_cast<Turn> (data); 
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const NetworkPacket& data){
    // encode the array first 
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            packet << data.board[i][j];
        }
    }
    // encode the turn 
    packet << data.turn;
    // encode who is the plyaer
    packet << data.player;
    return packet;
}

sf::Packet& operator >> (sf::Packet& packet, NetworkPacket& data){
    // decode the array first 
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            packet >> data.board[i][j];
        }
    }    
    // decode the turn 
    packet >> data.turn;
    // decode who is the plyaer
    packet >> data.player;
    return packet;
}
    
NetworkPacket makeNewNetworkPacket(){
    NetworkPacket packet; 
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            packet.board[i][j] = BoardState::EMPTY;
        }
    }

    packet.turn = Turn::CROSS_TURN; 
    return packet;
}

std::ostream& operator<<(std::ostream& os, const NetworkPacket& packet){
    switch(packet.player){
        case Player::CIRCLE:
            os << "Player: circle "; 
            break; 
        case Player::CROSS: 
            os << "Player: cross  "; 
            break;
    }

    switch(packet.turn){
        case Turn::CIRCLE_TURN:
            os << "Turn: circle"; 
            break; 
        case Turn::CROSS_TURN: 
            os << "Turn: cross"; 
            break;
    }

    return os;
}


sf::Packet& operator >> (sf::Packet& packet, UpdatePositionPacket& data){
    packet >> data.x >> data.y;
    return packet;
}
sf::Packet& operator << (sf::Packet& packet, const UpdatePositionPacket& data){
    packet << data.x << data.y;
    return packet;
}