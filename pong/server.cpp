#include "server.h"

sf::TcpSocket* Server::start()
{
    listener.listen(53000);
    std::cout << "Server listening on port " << std::endl;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    std::cout << ip;
    sf::TcpSocket* client = new sf::TcpSocket();
    listener.accept(*client);
    //std::cout << "Client connected: " << *client->getRemoteAddress() << std::endl;

    return client;
    //sf::Packet packet;
    //client.receive(packet);
    //std::string receivedData;
    //packet >> receivedData;
    //std::cout << "Received: " << receivedData << std::endl;
}
