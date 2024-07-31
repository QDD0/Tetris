#include <SFML/Graphics.hpp>
#include <iostream>

const unsigned int X = 400;
const unsigned int Y = 600;

class Tetris {
public:
};

class Menu {
public:
    void Program();
};

void Menu::Program() {
    sf::RenderWindow window(sf::VideoMode(X, Y), "Tetris");

    sf::RectangleShape button(sf::Vector2f(80, 20));
    button.setFillColor(sf::Color::Red);

    sf::Text text;
    sf::Text Windowtext;
    sf::Font font;

    if (!font.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Times New Roman.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    text.setFont(font);
    text.setString("Play");
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);

    Windowtext.setFont(font);
	Windowtext.setString("TETRIS");
	Windowtext.setCharacterSize(30);
	Windowtext.setFillColor(sf::Color::White);
    Windowtext.setPosition(150,200);

    button.setPosition(X / 2 - button.getSize().x / 2, Y / 2 - button.getSize().y / 2);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(button.getPosition().x + button.getSize().x / 2, button.getPosition().y + button.getSize().y / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(button);
        window.draw(Windowtext);
        window.draw(text);
        window.display();
    }
}

int main() {
    Menu menu;
    menu.Program();

    return 0;
}
