#include "Pletacka_alive.hpp"

/**
 * @brief Construct a new Pletacka_alive::Pletacka_alive object
 * 
 */
Pletacka_alive::Pletacka_alive()
{
 
}

Pletacka_alive::~Pletacka_alive()
{
}

void Pletacka_alive::init(PletackaConfig config)
{
    udpCfg.udpIP = config.udpIP;
    udpCfg.udpPort = config.udpPort;

    udpIP.fromString(udpCfg.udpIP);
    udp.begin(udpCfg.udpPort);
}

void Pletacka_alive::sendAlive(int sensorNumber)
{
    udpIP.fromString(udpCfg.udpIP);
    
    udp.beginPacket(udpIP, udpCfg.udpPort);
    udp.println(String(sensorNumber));
    udp.endPacket();
}

