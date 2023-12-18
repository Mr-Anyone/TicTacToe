#ifndef SHARED_HPP 
#define SHARED_HPP

#include <vector> 
#include <array> 
#include <SFML/Network.hpp>

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
typedef BoardState Player;

struct NetworkPacket{
    Board board;
    Turn turn;
    Player player; 
}; 

// useful operator overloads
sf::Packet& operator<< (sf::Packet& packet, const BoardState& state); 
sf::Packet& operator >> (sf::Packet& packet, BoardState& state);
sf::Packet& operator<< (sf::Packet& packet, const Turn& state);
sf::Packet& operator >> (sf::Packet& packet, Turn& state);
sf::Packet& operator << (sf::Packet& packet, const NetworkPacket& data);
sf::Packet& operator >> (sf::Packet& packet, NetworkPacket& data);
#endif