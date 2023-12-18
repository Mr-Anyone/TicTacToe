#ifndef STATE_H
#define STATE_H 

#include <mutex> 
#include "shared.hpp"

void sendData();

class GameWorld{
public:
    GameWorld();
    GameWorld(const NetworkPacket& packet);
    
    void updatePacket(const NetworkPacket& packet);
private:
    NetworkPacket m_state;
    std::mutex m_mutex;
}; 

#endif