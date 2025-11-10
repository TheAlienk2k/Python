#pragma once
#include "Scene.h"
#include "SceneMenager.h"
#include "LevelMenager.h"
#include "Snake.h"

#include <vector>
#include <array>
#include <string>

using namespace std;


class GameScene : public Scene
{
private:
	LevelMenager levelMenager;
	SceneMenager* sceneMenager;

	sf::Font titleFont;
	sf::Font buttonsFont;
	sf::Texture headTexture;
	sf::Text exitButton;

	const sf::Color snakeColor  = sf::Color::Green;
	const sf::Color boardWallColor = sf::Color::White;
	const int boardBlockSize = 32;
	const int boardMarginX = 50;
	const int boardMarginY = 50;
	const int boardBlockMargin = 5;

	vector<vector<char>> board;
	Snake snake;

public:
	GameScene(sf::RenderWindow &gameWindow, SceneMenager* menag, LevelMenager& levelMenag)
	:sceneMenager(menag)
	,levelMenager(levelMenag)
	,exitButton(buttonsFont)
	,board(levelMenager.getLevelBoard())
	,snake(levelMenag.getSnakeCordsAtStart()[0], levelMenag.getSnakeCordsAtStart()[1], levelMenag.getSnakeDirectionAtStart(), board)   //tymczasowa dla testu
	{
		if (!titleFont.openFromFile("Fonts/blocked.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}
		if (!buttonsFont.openFromFile("Fonts/blocks.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}

		if (!headTexture.loadFromFile("Textures/SnakeTextures/Head.png")) {
			cout << "Blad w ladowaniu tekstury glowy" << "\n";
		}

		exitButton.setFont(buttonsFont);
		exitButton.setString("EXIT>");
		exitButton.setCharacterSize(60);
		exitButton.setFillColor(sf::Color::White);
		exitButton.setPosition(sf::Vector2f((gameWindow.getSize().x - exitButton.getLocalBounds().size.x) - 20.0, 0.0));

	}

	void eventHandler(sf::Event event, sf::RenderWindow& gameWindow) override {
		if (event.is<sf::Event::MouseMoved>()) {
			if (exitButton.getFillColor() == sf::Color::White
				&& exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				exitButton.setString("EXIT >");
				exitButton.setFillColor(sf::Color::Red);
			}
			else if (exitButton.getFillColor() == sf::Color::Red
				&& !exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				exitButton.setString("EXIT>");
				exitButton.setFillColor(sf::Color::White);
			}
		}

		if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				sceneMenager->loadLevelSelectScene();
			}
		}

		if (auto key = event.getIf<sf::Event::KeyPressed>()) {
			snake.snakeDirectionChange(*key);
		}
	}

	void update(float deltaTime) override {
		snake.snakeMove(deltaTime);
	}
		
	void render(sf::RenderWindow& gameWindow) {
		gameWindow.draw(exitButton);
		renderCurrentBoardState(gameWindow);
		snakeRender(gameWindow);
	}

	void renderCurrentBoardState(sf::RenderWindow& gameWindow) {
		sf::RectangleShape block(sf::Vector2f(boardBlockSize, boardBlockSize));
		block.setFillColor(boardWallColor);

		int currentBlockX = boardMarginX;
		int currentBlockY = boardMarginY;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++)
			{
				if (board[i][j] == '#') {
					block.setPosition(sf::Vector2f(currentBlockX, currentBlockY));
					gameWindow.draw(block);
				}
				currentBlockX += boardBlockMargin + boardBlockSize;
			}
			currentBlockX = boardMarginX;
			currentBlockY += boardBlockMargin + boardBlockSize;
		}
	}

	void snakeRender(sf::RenderWindow& gameWindow) {
		sf::RectangleShape snakeBlock(sf::Vector2f(boardBlockSize, boardBlockSize));
		snakeBlock.setFillColor(snakeColor);

		bool isHead = true;

		for (array<int, 2> cord : snake.getSnakeCords()) {
			snakeBlock.setPosition(sf::Vector2f(boardMarginX + (cord[0] * (boardBlockMargin + boardBlockSize)), boardMarginY + (cord[1] * (boardBlockMargin + boardBlockSize))));
			gameWindow.draw(snakeBlock);

			if (isHead) {
				sf::Sprite snakeHead(headTexture);
				snakeHead.setTextureRect(sf::IntRect({ 0,0 }, { 32, 32 }));
				snakeHead.setOrigin(sf::Vector2f(snakeHead.getGlobalBounds().getCenter().x, snakeHead.getGlobalBounds().getCenter().y));
				snakeHead.setScale(sf::Vector2f(static_cast<float>(boardBlockSize)/32.f, static_cast<float>(boardBlockSize)/32.f));
				snakeHead.setPosition(sf::Vector2f(boardMarginX + (cord[0] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize/2), boardMarginY + (cord[1] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2)));

				if (snake.getDirection() == 'd') snakeHead.setRotation(sf::degrees(90.f));
				else if (snake.getDirection() == 's') snakeHead.setRotation(sf::degrees(180.f));
				else if (snake.getDirection() == 'a') snakeHead.setRotation(sf::degrees(270.f));
				
				gameWindow.draw(snakeHead);
				isHead = false;
			}
		}
	}

};

