#pragma once
#include "SFML/Network.hpp"
#include <iostream>

class Cclient
{
public:
    Cclient();
    ~Cclient();

    void connect();

private:
    sf::TcpSocket socket;
};