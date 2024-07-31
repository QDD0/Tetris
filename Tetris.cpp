#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

const unsigned int X = 360;
const unsigned int Y = 600;

enum class GameState {
    Menu,
    Game
};

class Tetris {
public:
    void Run();
};

class Square {
public:
    Square() {
        if (!texture.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Texturs\\Two.png")) {
            cout << "Failed to load texture" << endl;
        }
        block.setTexture(texture);
        block.setScale(0.16, 0.165);
        block.setPosition(position);
    }

    void Draw(sf::RenderWindow& window) const {
        window.draw(block);
    }

    void Move(float x, float y) {
        position.x += x;
        position.y += y;
        block.setPosition(position);
    }

    sf::Vector2f GetPosition() const {
        return position;
    }

private:
    sf::Vector2f position{ 0, 0 };  
    sf::Texture texture;
    sf::Sprite block;
};

class Menu {
public:
    void Display(sf::RenderWindow& window);
    bool HandleClick(sf::Vector2f mousePos);
};

class Game {
public:
    Game() : block(), isFalling(true) {}

    void Display(sf::RenderWindow& window);
    void Update(float deltaTime);

private:
    Square block;  
    float fallSpeed = 100.0f;  
    bool isFalling;  
};

void Menu::Display(sf::RenderWindow& window) {
    sf::RectangleShape Startbutton(sf::Vector2f(80, 20));
    Startbutton.setFillColor(sf::Color::Red);
    Startbutton.setPosition(X / 2 - Startbutton.getSize().x / 2, Y / 2 - Startbutton.getSize().y / 2);

    sf::Text text;
    sf::Text StartText;
    sf::Font font;
    sf::Font font2;

    sf::Image icon;
    if (!icon.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\icon.png")) {
        cout << "Failed to load icon" << endl;
    }

    if (!font.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Times New Roman.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    if (!font2.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Angeme-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    text.setFont(font);
    text.setString("Play");
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);

    StartText.setFont(font2);
    StartText.setString("TETRIS");
    StartText.setCharacterSize(30);
    StartText.setFillColor(sf::Color::White);
    StartText.setPosition(135, 180);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(Startbutton.getPosition().x + Startbutton.getSize().x / 2, Startbutton.getPosition().y + Startbutton.getSize().y / 2);

    window.clear();
    window.draw(Startbutton);
    window.draw(StartText);
    window.draw(text);
    window.display();
}

bool Menu::HandleClick(sf::Vector2f mousePos) {
    sf::RectangleShape button(sf::Vector2f(80, 20));
    button.setPosition(X / 2 - button.getSize().x / 2, Y / 2 - button.getSize().y / 2);

    return button.getGlobalBounds().contains(mousePos);
}

void Game::Display(sf::RenderWindow& window) {
    window.clear();

    int cellSize = 30;
    int numVerticalLines = window.getSize().x / cellSize + 1;
    int numHorizontalLines = window.getSize().y / cellSize + 1;

    sf::VertexArray grid(sf::Lines);

    for (int i = 0; i <= numVerticalLines; ++i) {
        float x = i * cellSize;
        grid.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color::White));
        grid.append(sf::Vertex(sf::Vector2f(x, window.getSize().y), sf::Color::White));
    }

    for (int i = 0; i <= numHorizontalLines; ++i) {
        float y = i * cellSize;
        grid.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::White));
        grid.append(sf::Vertex(sf::Vector2f(window.getSize().x, y), sf::Color::White));
    }

    window.draw(grid);
    block.Draw(window);
    window.display();
}

void Game::Update(float deltaTime) {
    if (isFalling) {
        block.Move(0, fallSpeed * deltaTime);
        
        if (block.GetPosition().y + 61 > Y) {  
            isFalling = false;
        }
    }
}

void Tetris::Run() {
    sf::RenderWindow window(sf::VideoMode(X, Y), "Tetris", sf::Style::Close | sf::Style::Titlebar);
    GameState state = GameState::Menu;
    Menu menu;
    Game game;

    sf::Clock clock;  

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

        float deltaTime = clock.restart().asSeconds();  

        if (state == GameState::Menu) {
            menu.Display(window);
        }
        else if (state == GameState::Game) {
            game.Update(deltaTime);  
            game.Display(window);
        }
    }
}

int main() {
    Tetris tetris;
    tetris.Run();

    return 0;
}
