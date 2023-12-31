#include "game.h"
#include <iostream>
#include <sstream>


Game::Game(sf::RenderWindow* window, bool client, sf::TcpSocket* socket) :client(client), socket(socket), window(window), greenBall(20), greenBallServer(20) {
    greenBall.setFillColor(sf::Color::Green);
    greenBall.setPosition(100, 100);
    greenBallServer.setFillColor(sf::Color::Blue);
    greenBallServer.setPosition(110, 110);
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
            this->packet = "" + std::to_string(greenBall.getPosition().x) + ":" + std::to_string(greenBall.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            greenBall.move(-0.5, 0);
            this->packet = "" + std::to_string(greenBall.getPosition().x) + ":" + std::to_string(greenBall.getPosition().y);
            //this->packet = "A";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            greenBall.move(0, 0.5);
            this->packet = "" + std::to_string(greenBall.getPosition().x) + ":" + std::to_string(greenBall.getPosition().y);
            //this->packet = "S";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            greenBall.move(0.5, 0);
            this->packet = "" + std::to_string(greenBall.getPosition().x) + ":" + std::to_string(greenBall.getPosition().y);
            //this->packet = "D";
        }
    }
    else if (!client)
    {
        this->packet = "N";
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            greenBallServer.move(0, -0.5);
            this->packet = "" + std::to_string(greenBallServer.getPosition().x) + ":" + std::to_string(greenBallServer.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            greenBallServer.move(-0.5, 0);
            this->packet = "" + std::to_string(greenBallServer.getPosition().x) + ":" + std::to_string(greenBallServer.getPosition().y);
            //this->packet = "A";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            greenBallServer.move(0, 0.5);
            this->packet = "" + std::to_string(greenBallServer.getPosition().x) + ":" + std::to_string(greenBallServer.getPosition().y);
            //this->packet = "S";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            greenBallServer.move(0.5, 0);
            this->packet = "" + std::to_string(greenBallServer.getPosition().x) + ":" + std::to_string(greenBallServer.getPosition().y);
            //this->packet = "D";
        }
    }
}

void Game::render() {
    //std::cout << this->greenBallServer.getPosition().x << std::endl;
    //std::cout << this->greenBallServer.getPosition().y << std::endl;
    //std::cout << this->greenBall.getPosition().x << std::endl;
    //std::cout << this->greenBall.getPosition().y << std::endl;
    window->clear();
    window->draw(greenBall);
    window->draw(greenBallServer);
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
    else if(!client)
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

        sf::Vector2f pos = {100,100};

        if (packet != "N")
        {
            std::istringstream ss(packet);

            if (std::getline(ss, packet, ':')) {
                pos.x = std::stof(packet); // Convert the string to float 
            }

            // Read the second float value
            if (std::getline(ss, packet, ':')) {
                pos.y = std::stof(packet); // Convert the string to float 
            }

            greenBall.setPosition(pos);

        }

        //iss >> x delimiter >> y;

        /*if (packet == "W")
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
        }*/

    }
    else if (client)
    {
        sf::Packet p;
        socket->receive(p);
        p >> (packet);

        sf::Vector2f pos = { 100,100 };

        if (packet != "N")
        {
            std::istringstream ss(packet);

            if (std::getline(ss, packet, ':')) {
                pos.x = std::stof(packet); // Convert the string to float 
            }

            // Read the second float value
            if (std::getline(ss, packet, ':')) {
                pos.y = std::stof(packet); // Convert the string to float 
            }

            greenBallServer.setPosition(pos);

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