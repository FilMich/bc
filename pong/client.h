#include <SFML/Network.hpp>
#include <iostream>

class Client
{
public:
    Client() {};
    ~Client() {};
    void sendData(std::string data);
    sf::TcpSocket* connect();
private:
    sf::TcpSocket socket; 
};
