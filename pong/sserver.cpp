#include "sserver.h"

Sserver::Sserver()
{
}

Sserver::~Sserver()
{
}

std::vector<sf::TcpSocket*>& Sserver::getPlayers()
{
    return players;
}

void Sserver::Run()
{
    while (true) {
        listener.listen(53000); // Port number
        selector.add(listener);
        if (selector.wait()) {
            // Check if the listener socket is ready to accept a new connection
            if (selector.isReady(listener)) {
                sf::TcpSocket* newClient = new sf::TcpSocket;
                if (listener.accept(*newClient) == sf::Socket::Done) {
                    std::cout << "New client connected: " << newClient->getRemoteAddress() << std::endl;
                    selector.add(*newClient);

                    players.push_back(newClient);

                    // Assign a color to the new player and store in the vector
                    //PlayerInfo player;
                    //player.socket = newClient;
                    //player.color = sf::Color::Red; // Assign a color
                    //players.push_back(player);
                }
                else {
                    delete newClient;
                }
            }

            // Check all connected clients for data
            for (sf::TcpSocket* player : players) {
                if (selector.isReady(*player)) {
                    sf::Packet packet;
                    if (player->receive(packet) == sf::Socket::Done) {
                        // Handle received data from the client if needed
                    }
                }
            }
        }
    }
}

