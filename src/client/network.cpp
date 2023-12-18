#include "network.hpp"
#include <iostream> 
#include <SFML/Network.hpp>

void sendData(){ 
    std::cout << "I am going to send some data packet" << std::endl;
    sf::TcpSocket socket; 

    sf::IpAddress address = sf::IpAddress::resolve("127.0.0.1").value();
    std::cout << "connecting to address: " << address.toString() << std::endl;
    sf::Socket::Status status = socket.connect(address, 10000);
    if(status != sf::Socket::Status::Done){
        std::cout << "cannot connect to address" << std::endl;
    }

    std::string some_message = "Do you hear me?";
    sf::Packet packet;
    packet << some_message;

    if(socket.send(packet) != sf::Socket::Status::Done){
        std::cout << "Cannot send I see you packet" << std::endl;
    }else{
        std::cout << "I've send an message" << std::endl;
    }

}
