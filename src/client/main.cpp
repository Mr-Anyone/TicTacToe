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
        NetworkPacket data; 
        packet >> data; 
        game_world->updatePacket(data);

        std::this_thread::sleep_for(std::chrono::milliseconds (500));
    }
}

void draw_board(const sf::Font& font, std::shared_ptr<GameWorld> game_world, sf::RenderWindow& window){
    // clearing the screen
    window.clear(sf::Color::White);
    NetworkPacket data = game_world->getPacket();
    
    // displyaing player
    {
        sf::Text text (font);
        text.setString("Player: Cross"); 
        text.setCharacterSize(15); 
        text.setFillColor(sf::Color::Blue); 
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

    // displaying turn 
    {
        sf::Text text (font);
        text.setPosition({0, 15}); 
        text.setString("Turn: Cross"); 
        text.setCharacterSize(15); 
        text.setFillColor(sf::Color::Blue); 
        switch(data.turn){
            case Turn::CIRCLE_TURN: 
                text.setString("Turn: Circle"); 
                break;
            case Turn::CROSS_TURN:
                text.setString("Turn: Cross"); 
                break;
        }
        window.draw(text);
    }


    //drawing board
    float width = window.getSize().x;
    float height = window.getSize().y;
    float width_dx = width / 3; 
    float height_dx = height / 3;
    // drawing vertical line
    sf::RectangleShape vertical_line (sf::Vector2f(2.f, height));
    vertical_line.setPosition({width_dx, 0}); 
    vertical_line.setFillColor(sf::Color::Black); 
    window.draw(vertical_line);
    vertical_line.setPosition({width_dx * 2, 0}); 
    vertical_line.setFillColor(sf::Color::Black); 
    window.draw(vertical_line);
    // drawing horizontal line 
    sf::RectangleShape horizontal_line (sf::Vector2f(width, 2.0));
    horizontal_line.setPosition({0, height_dx}); 
    horizontal_line.setFillColor(sf::Color::Black); 
    window.draw(horizontal_line);
    horizontal_line.setPosition({0, height_dx * 2}); 
    horizontal_line.setFillColor(sf::Color::Black); 
    window.draw(horizontal_line);

    // drawing the pieces on the board 
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            if(data.board[i][j] == BoardState::CIRCLE){
                float circle_y = height / 3.f * (i + 1) - height_dx / 2; 
                float circle_x = width / 3.f * (j + 1) - width_dx / 2; 

                sf::CircleShape circle (50);
                circle.setFillColor(sf::Color::Green);
                circle.setPosition({circle_x, circle_y}); 
                circle.setOrigin({50, 50});
                window.draw(circle);
            }

            if(data.board[i][j] == BoardState::CROSS){
                float circle_y = height / 3.f * (i + 1) - height_dx / 2; 
                float circle_x = width / 3.f * (j + 1) - width_dx / 2; 
                
                sf::CircleShape circle (50);
                circle.setFillColor(sf::Color::Cyan);
                circle.setPosition({circle_x, circle_y}); 
                circle.setOrigin({50, 50});
                window.draw(circle);
            }
        }
    }

}

void sendData(sf::Event& event, sf::RenderWindow& window, std::shared_ptr<GameWorld> world, std::shared_ptr<sf::TcpSocket> socket){
    // not your turn do not send packet
    NetworkPacket data = world->getPacket(); 
    if(data.player != data.turn){
        return;
    }

    // sending data I guess
    int mouse_x = event.mouseButton.x; 
    int mouse_y = event.mouseButton.y;

    // sending that position packet 
    float width_dx = window.getSize().x / 3.f;
    float height_dy = window.getSize().y / 3.f;

    int position_x = static_cast<int> (mouse_x / width_dx);
    int position_y = static_cast<int> (mouse_y / height_dy);

    UpdatePositionPacket updatePosition;
    updatePosition.x = position_y; 
    updatePosition.y = position_x; 
    sf::Packet packet; 
    packet << updatePosition; 
    
    std::cout << "I am sending packet" << std::endl;
    if(socket->send(packet) != sf::Socket::Status::Done){
        std::cout << "We have lost packet" << std::endl; 
        exit(-1);
    }

}

int main(){
    std::string ip_address;
    std::cout << "ip address input: ";
    std::cin >> ip_address; 
    std::cout << "connecting to address: " << ip_address << std::endl;
    
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
    if(!font.loadFromFile("Starborn.ttf")){
        std::cout << "cannot load font" << std::endl; 
        return -1;
    }

    // entering game loop
    while(window.isOpen()){
        sf::Event event; 
        draw_board(font, game_world, window);

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::MouseButtonReleased)
                sendData(event, window, game_world, socket);
        }

        window.display();
    }

    std::cout << "Program ended" << std::endl; 
    return 0;
}
