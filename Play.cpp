#pragma once
#include "Play.h"
#include <vector>

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
        grid.append(sf::Vertex(sf::Vector2f(x, 30), sf::Color::White));
        grid.append(sf::Vertex(sf::Vector2f(x, window.getSize().y), sf::Color::White));
    }

    for (int i = 0; i <= numHorizontalLines; ++i) {
        float y = i * cellSize;
        grid.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::White));
        grid.append(sf::Vertex(sf::Vector2f(window.getSize().x, y), sf::Color::White));
    }

    window.draw(grid);
    block.Draw(window);
    block4.Draw(window);
    window.display();
}

void Game::Update(float deltaTime) {
    vector <sf::Vector2f> exe;
    exe.push_back(block.GetPosition());
	exe.push_back(block2.GetPosition());
	exe.push_back(block3.GetPosition());
	exe.push_back(block4.GetPosition());
	
    if (isFalling) {
        block.Move(0, fallSpeed * deltaTime);
        block2.Move(0, fallSpeed * deltaTime);

        if (block.GetPosition().y + 61 > Y) {
            isFalling = false;
        }

        if(block2.GetPosition().y + 123 > Y) {
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

            if (state == GameState::Game) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::A) {
                        game.block.Move(-10, 0);
                    }
                    else if (event.key.code == sf::Keyboard::D) {
                        game.block.Move(10, 0);
                    }
                    else if (event.key.code == sf::Keyboard::S) {
                        game.block.Move(0, 10);
                    }
                    else if (event.key.code == sf::Keyboard::W) {
                        game.block.Rotate(); // Вращение фигуры
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (state == GameState::Game) {
            game.Update(deltaTime);
            game.Display(window);
        }
        else if (state == GameState::Menu) {
            menu.Display(window);
        }
    }
}
