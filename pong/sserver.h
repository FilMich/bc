#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"

class Sserver
{
public:
	Sserver();
	~Sserver();
	std::vector<sf::TcpSocket*>& getPlayers();

    void Run();

private:
	sf::TcpListener listener;
	sf::SocketSelector selector;
    std::vector<sf::TcpSocket*> players;
};

