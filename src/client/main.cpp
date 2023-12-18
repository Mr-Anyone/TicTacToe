#include <iostream>
#include<SFML/Graphics.hpp>
#include <thread>
#include <memory> 

#include "game.hpp"
#include "state.hpp"

void background_update(std::shared_ptr<sf::TcpSocket> socket, std::shared_ptr<GameWorld>  game_world){
    std::cout << "This is just some sort of background update I guess" << std::endl;
    // getting the first I got you socket message
    sf::Packet packet; 
    if(socket->receive(packet) != sf::Socket::Status::Done){
        std::cout << "Did not get the I receive packet for some reasons. Exit code" << std::endl; 
        exit(-1);
    }
    
    NetworkPacket data; 
    packet >> data; 
    game_world->updatePacket(data);
    std::cout << "I got data: " << data << std::endl;

    while(true){
        sf::Packet packet;
        if(socket->receive(packet) != sf::Socket::Status::Done){
            std::cout << "cannot receive packet for some reason: exit code" << std::endl;
            exit(-1);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds (500));
    }
}


void draw_board(const sf::Font& font, std::shared_ptr<GameWorld> game_world, sf::RenderWindow& window){
    // clearing the screen
    window.clear(sf::Color::White);

    sf::Text text (font);
    text.setString("Player: Cross"); 
    text.setCharacterSize(25); 
    text.setFillColor(sf::Color::Blue); 
    
    NetworkPacket data = game_world->getPacket();
    
    // drawing the font
    switch(data.player){
        case Player::CIRCLE:
            text.setString("Player: Circle");
            break;
        case Player::CROSS: 
            text.setString("Player: Cross");
            break;
    }
    window.draw(text);
}

int main(){
    std::string ip_address = "127.0.0.1";
    int port = 10000;
    sf::IpAddress address = sf::IpAddress::resolve(ip_address).value();
    
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket> (); 
    if (socket->connect(address, port) != sf::Socket::Status::Done) {
        std::cout << "Cannot connect to socket" << std::endl;
        return -1;
    }

    std::shared_ptr<GameWorld> game_world = std::make_shared<GameWorld> (); 
    std::thread thread (background_update, socket, game_world);

    // creating the windows and stuff
    sf::Vector2u window_size  (500, 500);
    std::string window_title = "Tictactoe";
    sf::VideoMode video_mode (window_size); 
    sf::RenderWindow window {video_mode, window_title};

    //loading font
    sf::Font font;
    if(!font.loadFromFile("C:\\Users\\Vince\\Documents\\vscode\\TicTacToe\\Starborn.ttf")){
        std::cout << "cannot load font" << std::endl; 
        return -1;
    }

    // entering game loop
    while(window.isOpen()){
        sf::Event event; 
        draw_board(font, game_world, window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
    }

    std::cout << "Program ended" << std::endl; 
    return 0;
}
