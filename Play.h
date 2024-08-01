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

	void Rotate() {
		block.setRotation(block.getRotation() + 90);
	}

private:
    sf::Vector2f position{ 150, 30 };
    sf::Texture texture;
    sf::Sprite block;
};

class Line {
public:
    Line() {
        if (!texture2.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Texturs\\Four.png")) {
            cout << "Failed to load texture" << endl;
        }
        block2.setTexture(texture2);
        block2.setScale(0.05, 0.05);
        block2.setRotation(90);
        block2.setPosition(position2);
    }

	void Draw(sf::RenderWindow& window) const {
		window.draw(block2);
	}

	void Move(float x, float y) {
		position2.x += x;
		position2.y += y;
		block2.setPosition(position2);
	}

	sf::Vector2f GetPosition() const {
		return position2;
	}

    void Rotate() {
		block2.setRotation(block2.getRotation() + 90);
	}

private:
	sf::Vector2f position2{ 150, 30 };
	sf::Texture texture2;
	sf::Sprite block2;
};

class Triangle {
public:
    Triangle() {
        if (!texture3.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Texturs\\Five.png")) {
            cout << "Failed to load texture" << endl;
        }
        block3.setTexture(texture3);
        block3.setScale(0.05, 0.05);
        block3.setPosition(position3);
    }

	void Draw(sf::RenderWindow& window) const {
		window.draw(block3);
	}

	void Move(float x, float y) {
		position3.x += x;
		position3.y += y;
		block3.setPosition(position3);
	}

	sf::Vector2f GetPosition() const {
		return position3;
	}

	void Rotate() {
		block3.setRotation(block3.getRotation() + 90);
	}

private:
    sf::Vector2f position3{ 150, 10 };
	sf::Texture texture3;
	sf::Sprite block3;
};

class FigursT {
public:
    FigursT() {
		if (!texture4.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Texturs\\Three.png")) {
			cout << "Failed to load texture" << endl;
		}
		block4.setTexture(texture4);
		block4.setScale(0.16, 0.165);
		block4.setPosition(position4);
    }

	void Draw(sf::RenderWindow& window) const {
		window.draw(block4);
	}

	void Move(float x, float y) {
		position4.x += x;
		position4.y += y;
		block4.setPosition(position4);
	}

	sf::Vector2f GetPosition() const {
		return position4;
	}

	void Rotate() {
		block4.setRotation(block4.getRotation() + 90);
	}

private:
	sf::Vector2f position4{ 150, 30 };
	sf::Texture texture4;
	sf::Sprite block4;
};

class FigurN {
public:
	FigurN() {
		if (!texture5.loadFromFile("C:\\Users\\denis\\Desktop\\Project\\Tetris\\Texturs\\One.png")) {
			cout << "Failed to load texture" << endl;
		}
		block5.setTexture(texture5);
		block5.setScale(0.16, 0.165);
		block5.setPosition(position5);
	}

	void Draw(sf::RenderWindow& window) const {
		window.draw(block5);
	}

	void Move(float x, float y) {
		position5.x += x;
		position5.y += y;
		block5.setPosition(position5);
	}

	sf::Vector2f GetPosition() const {
		return position5;
	}

	void Rotate() {
		block5.setRotation(block5.getRotation() + 90);
	}

private:
	sf::Vector2f position5{ 150, 30 };
	sf::Texture texture5;
	sf::Sprite block5;
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

    Square block;
    Line block2;
	Triangle block3;
	FigursT block4;
	FigurN block5;
    float fallSpeed = 100.0f;
    bool isFalling;
};