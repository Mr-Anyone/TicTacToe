#include <iostream> 
#include <SFML/Network.hpp>

#include "network.hpp"
#include "shared.hpp"

void sendData(){ 
    std::cout << "I am going to send some data packet" << std::endl;
    sf::TcpSocket socket; 

    sf::IpAddress address = sf::IpAddress::resolve("127.0.0.1").value();
    std::cout << "connecting to address: " << address.toString() << std::endl;
    sf::Socket::Status status = socket.connect(address, 10000);
    if(status != sf::Socket::Status::Done){
        std::cout << "cannot connect to address" << std::endl;
    }

   sf::Packet packet; 
   NetworkPacket data;
   if(socket.receive(packet) != sf::Socket::Status::Done){
        std::cout << "cannot receive data for some reason" << std::endl;
        exit(-1);
   }
   
   packet >> data; 
   std::cout << data << std::endl;
}
