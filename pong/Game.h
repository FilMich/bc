#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
class Game {
public:
    Game(sf::RenderWindow* window, bool client, sf::TcpSocket* socket);
    ~Game();

    void run();

    sf::Vector2f getPos() {
        return sf::Vector2f(greenBall.getPosition().x, greenBall.getPosition().y);
    }
    bool getMoved() {
        return this->moved;
    }
private:
    sf::RenderWindow* window;
    sf::CircleShape greenBall;
    sf::CircleShape greenBallServer;
    sf::Clock clock;
    bool moved = false;
    bool canStart = false;
    bool client;
    std::string packet = "";
    sf::TcpSocket* socket;
    void processEvents();
    void update();
    void render();
    void updateToSerer();
    void updateFromSerer();
    //void setValues(int x, int y);
};