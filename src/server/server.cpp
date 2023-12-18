#include <iostream>
#include <SFML/Network.hpp>
#include <thread>


int main(){
    sf::TcpListener listener;

    if (listener.listen(10000) != sf::Socket::Status::Done){
        std::cout << "I cannot be binded to address" << std::endl;
        return -1;
    }
    
    std::cout << "setup listener" << std::endl;

    sf::TcpSocket socket; 
    if(listener.accept(socket) != sf::Socket::Status::Done){
        std::cout << "I cannot accept a socket for some reason" << std::endl;
        return -1;
    }

    std::cout << "I've accepted a socket" << std::endl;
    sf::Packet packet;
    std::string message;
    std::this_thread::sleep_for(std::chrono::seconds (1));
    
    if(socket.receive(packet) == sf::Socket::Status::Done){
        if(packet >> message){
            std::cout << "I got your packet message: " << message << std::endl;
        }else{
            std::cout <<"I did not got your message" << std::endl;
        }
    }

    std::cout << "The server is now closed!" << std::endl;
    return 0;
}