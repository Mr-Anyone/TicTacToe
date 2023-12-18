#include <iostream>
#include<SFML/Graphics.hpp>

#include"network.hpp"
#include "game.hpp"

int main(){
    Board board = makeBoard();
    // starting with cross turn
    Turn turn = Turn::CROSS_TURN;

    sendData();
    
    // sf::Vector2u window_size  (500, 500);
    // std::string window_title = "Tictactoe";
    // sf::VideoMode video_mode (window_size); 
    // sf::RenderWindow window {video_mode, window_title};

    // while(window.isOpen()){
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear(sf::Color::White);
    //     window.display();
    // }

    std::cout << "Program ended" << std::endl; 
    return 0;
}
