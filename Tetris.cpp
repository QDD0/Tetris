#include <SFML/Graphics.hpp>
#include <iostream>

const unsigned int X = 400;
const unsigned int Y = 600;

enum class GameState {
    Menu,
    Game
};

class Tetris {
public:
    void Run();
};

class Menu {
public:
    void Display(sf::RenderWindow& window);
    bool HandleClick(sf::Vector2f mousePos);
};

class Game {
public:
    void Display(sf::RenderWindow& window);
};

void Menu::Display(sf::RenderWindow& window) {
    sf::RectangleShape button(sf::Vector2f(80, 20));
    button.setFillColor(sf::Color::Red);
    button.setPosition(X / 2 - button.getSize().x / 2, Y / 2 - button.getSize().y / 2);

    sf::Text text;
    sf::Text StartText;
    sf::Font font;

    if (!font.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Times New Roman.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    text.setFont(font);
    text.setString("Play");
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);

	StartText.setFont(font);
	StartText.setString("TETRIS");
	StartText.setCharacterSize(30);
	StartText.setFillColor(sf::Color::White);
    StartText.setPosition(150, 200);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(button.getPosition().x + button.getSize().x / 2, button.getPosition().y + button.getSize().y / 2);

    window.clear();
    window.draw(button);
	window.draw(StartText);
    window.draw(text);
    window.display();
}

bool Menu::HandleClick(sf::Vector2f mousePos) {
    sf::RectangleShape button(sf::Vector2f(80, 20));
    button.setPosition(X / 2 - button.getSize().x / 2, Y / 2 - button.getSize().y / 2);

    if (button.getGlobalBounds().contains(mousePos)) {
        return true;
    }
    return false;
}

void Game::Display(sf::RenderWindow& window) {
    window.clear();
    // Отображение игрового экрана (здесь можно добавить игровой контент)
    window.display();
}

void Tetris::Run() {
    sf::RenderWindow window(sf::VideoMode(X, Y), "Tetris");
    GameState state = GameState::Menu;
    Menu menu;
    Game game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (state == GameState::Menu && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (menu.HandleClick(mousePos)) {
                        state = GameState::Game;
                    }
                }
            }
        }

        if (state == GameState::Menu) {
            menu.Display(window);
        }
        else if (state == GameState::Game) {
            game.Display(window);
        }
    }
}

int main() {
    Tetris tetris;
    tetris.Run();

    return 0;
}
