#pragma once
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