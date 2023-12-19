#include "game.h"
#include <iostream>
Game::Game(sf::RenderWindow* window, bool client, sf::TcpSocket* socket) :client(client), socket(socket), window(window), greenBall(20) {
    greenBall.setFillColor(sf::Color::Green);
    greenBall.setPosition(100, 100);
}

Game::~Game() {
}

void Game::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Game::update() {
    if (client)
    {
        this->packet = "N";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            greenBall.move(0, -0.5 );
            this->packet = "W";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            greenBall.move(-0.5, 0);
            this->packet = "A";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            greenBall.move(0, 0.5);
            this->packet = "S";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            greenBall.move(0.5, 0);
            this->packet = "D";
        }
    }
}

void Game::render() {
    window->clear();
    window->draw(greenBall);
    window->display();
}

void Game::updateToSerer()
{
    if (client)
    {
        sf::Packet p;
        p << (packet);
        socket->send(p);
    }
}

void Game::updateFromSerer()
{
    if (!client)
    {
        sf::Packet p;
        socket->receive(p);
        p >> (packet);


        if (packet == "W")
        {
            greenBall.move(0, -0.5);
        }
        else if (packet == "A")
        {
            greenBall.move(-0.5, 0);
        }
        else if (packet == "S")
        {
            greenBall.move(0, 0.5);
        }
        else if (packet == "D")
        {
            greenBall.move(0.5, 0);
        }

    }
}

void Game::run() {
    while (window->isOpen()) {
        processEvents();
        update();
        updateToSerer();
        updateFromSerer();
        render();
    }
}