#include "lobby.h"

Lobby::Lobby(sf::RenderWindow* window, Sserver& server) : server(server) {
    this->window = window;
}

Lobby::~Lobby()
{
}

void Lobby::run()
{
    while (window->isOpen()) {
        //Update();
        DrawPlayers();

        window->clear();
        window->display();
    }
}

void Lobby::DrawPlayers()
{
    colors.push_back(sf::Color::Blue);
    colors.push_back(sf::Color::Green);
    colors.push_back(sf::Color::Yellow);
    colors.push_back(sf::Color::Cyan);
    colors.push_back(sf::Color::Magenta);
    colors.push_back(sf::Color::Red);

    int r = 0;

    for (sf::TcpSocket* client : server.getPlayers()) {
        sf::Color& color = colors[r];
        r++;
        if (r > 6)
        {
            r = 0;
        }
        sf::CircleShape playerCircle(20); // Radius of the circle
        playerCircle.setFillColor(color);
        // Set position based on player information
        // Draw the player circle on the window
        window->draw(playerCircle);
    }
}
