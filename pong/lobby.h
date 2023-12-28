#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "sserver.h"

class Lobby
{
public:
    Lobby(sf::RenderWindow* window, Sserver& server);
	~Lobby();

    void run();

private:
    std::vector<sf::Color> colors;
    Sserver& server;
	sf::RenderWindow* window;
    void DrawPlayers();
};