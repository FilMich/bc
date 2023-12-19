#include <SFML/Network.hpp>
#include <iostream>

class Server
{
public:
	Server() {};
	~Server() {};
	sf::TcpSocket* start();
private:
	sf::TcpListener listener;
};