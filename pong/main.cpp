#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "server.h"
#include "client.h"
#include "Game.h"

int main() {
	
	std::cout << "Enter 1 for server or 2 for client: ";
	int c;
	std::cin >> c;
	
	sf::TcpSocket* socket;

	if (c == 1)
	{
		Server server;
		socket = server.start();


		sf::RenderWindow win(sf::VideoMode(800, 600), "server");
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