#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "server.h"
#include "client.h"
#include "Game.h"
#include "sserver.h"
#include <thread>
#include "cclient.h"
#include "lobby.h"

int main() {

//	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//
//	std::cout << "Enter 1 for server or 2 for client: ";
//	int c;
//	std::cin >> c;
//
//
//	Sserver server;
//
//	if (c == 1)
//	{
//		std::thread serverThread(&Sserver::Run, &server);
//
//		serverThread.join();
//	}
//	else if(c == 2)
//	{
//		Cclient client;
//		client.connect();
//	}
//
//	//Sserver server;
//	//std::thread serverThread(&Sserver::Run, &server);
//
//	//Cclient client;
//	//client.connect();
//
//	sf::RenderWindow win(sf::VideoMode(800, 600), "game", sf::Style::Default);
//
//	Lobby lobby(&win, server);
//	lobby.run();
//
//}



	//std::cout << "Enter 1 for server or 2 for client: ";
	int c = 0;
	//std::cin >> c;

	sf::RenderWindow wind(sf::VideoMode(800, 600), "server");
	while (c == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			c = 1;
			wind.close();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			c = 2;
			wind.close();
		}
	}
	

	
	
	sf::TcpSocket* socket;

	if (c == 1)
	{
		sf::RenderWindow win(sf::VideoMode(800, 600), "server");
		Server server;
		socket = server.start();


		//sf::RenderWindow win(sf::VideoMode(800, 600), "server");
		
		Game* game = new Game(&win, false, socket);
		game->run();
	}
	else if(c == 2)
	{
		Client client;
		socket = client.connect();


		/*std::string data_to_send;
		std::cout << "Enter data to send: ";
		std::cin >> data_to_send;
		client.sendData(data_to_send);*/
		sf::RenderWindow win(sf::VideoMode(800, 600), "client");
		Game* game = new Game(&win, true, socket);
		game->run();
	}
	return 0;
}
















//#include "menu.h"
//
//#include "game.h"
//
//
//
//
//int main() {
//	Menu* menu = new Menu();
//	menu->run_menu();
//	delete menu;
//	menu = nullptr;
//	return EXIT_SUCCESS;
//}