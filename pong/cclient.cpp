#include "cclient.h"

Cclient::Cclient()
{
}

Cclient::~Cclient()
{
}

void Cclient::connect()
{
    if (socket.connect("192.168.1.106", 53000) != sf::Socket::Done) {
        std::cerr << "Failed to connect to the server" << std::endl;
    }
}
