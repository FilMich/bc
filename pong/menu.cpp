#include "menu.h"



Menu::Menu() {
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu() {
    delete window;
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::set_values() {
    window->create(sf::VideoMode(1280, 720), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(0, 0));

    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("./ethn.otf");
    image->loadFromFile("./menu-sci-fi-game.png");

    bg->setTexture(*image);

    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };

    options = { "My Game", "Play", "Settings", "About", "Exit" };
    texts.resize(5);
    coords = { {590,40},{610,191},{590,282},{600,370},{623,457} };
    sizes = { 20,28,24,24,24 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(4);
    pos = 1;

    winclose->setSize(sf::Vector2f(23, 26));
    winclose->setPosition(1178, 39);
    winclose->setFillColor(sf::Color::Transparent);
    currentState = GameState::Menu;

}

void Menu::loop_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
            if (pos < 4) {
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
            if (pos > 1) {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
            theselect = true;
            if (pos == 1) {
                currentState = GameState::Play;
                initPlayState();
            }
            else if (pos == 4) {
                window->close();
            }
            std::cout << options[pos] << '\n';
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (winclose->getGlobalBounds().contains(mouse_coord)) {
                //std::cout << "Close the window!" << '\n';
                window->close();
            }
            if (texts[1].getGlobalBounds().contains(mouse_coord))
            {
                currentState = GameState::Play;
                initPlayState();
            }
        }
    }
}

void Menu::draw_all() {
    window->clear();
    window->draw(*bg);
    for (auto t : texts) {
        window->draw(t);
    }
    window->display();
}

void Menu::run_menu() {
    sf::CircleShape greenBall(20);
    greenBall.setFillColor(sf::Color::Green);
    greenBall.setPosition(100, 100);
    while (window->isOpen()) {

        if (currentState == GameState::Menu) {
            loop_events();
            draw_all();
        }
        else if (currentState == GameState::Play)
        {

            window->clear();
            window->draw(greenBall);
            window->display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                greenBall.move(0, -0.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                greenBall.move(-0.5, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                greenBall.move(0, 0.5);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                greenBall.move(0.5, 0);
            }
        }
    }
}

void Menu::initPlayState() {
    // Add any game initialization logic here
}