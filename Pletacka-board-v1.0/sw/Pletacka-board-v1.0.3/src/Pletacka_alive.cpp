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

void Pletacka_alive::init(PletackaConfig* config, Pletacka_UI* inUI)
{
    UI = inUI;
	cfg = config;

    udpIP.fromString(cfg->udpIP);
    udp.begin(cfg->udpPort);
}

void Pletacka_alive::sendAlive(int sensorNumber)
{
    udpIP.fromString(cfg->udpIP);
    
    udp.beginPacket(udpIP, cfg->udpPort);
    udp.println(String(sensorNumber));
    udp.endPacket();
}

