#include "client.h"

void Client::sendData(std::string data)
{
    sf::Packet packet;
    packet.operator<<(data);
    socket.send(packet);
}

sf::TcpSocket* Client::connect()
{
    if (socket.connect("192.168.1.106", 53000) == sf::Socket::Done) {
        std::cout << "Connected to server" << std::endl;
        return &socket;
    }
    else {
        std::cerr << "Failed to connect to the server." << std::endl;
        return NULL;
    }
}
