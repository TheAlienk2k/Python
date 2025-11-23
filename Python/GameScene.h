#pragma once
#include "Scene.h"
#include "SceneMenager.h"
#include "LevelMenager.h"
#include "Snake.h"
#include "FoodMenager.h"
#include "Food.h"

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
	sf::Text scoreText;
	
	sf::RectangleShape menuBackGround;
	vector<sf::Text*> pauseMenuButtons;
	double pauseMenuButtonHeight = 0;
	double pauseMenuButtonSpacing = 60;
	sf::Text exitButton;

	const sf::Color snakeColor  = sf::Color::Green;
	const sf::Color boardWallColor = sf::Color::White;
	const int boardBlockSize = 32;
	const int boardMarginX = 50;
	const int boardMarginY = 50;
	const int boardBlockMargin = 5;
	bool isPaused = false;

	int heightOfBoard;
	const sf::Color effectTimerColor = sf::Color::Green;
	const int effectBlockSize = 52;
	const int effectMarginX = 70;
	const int effectMarginY = 50;
	const int effectBlockMargin = 4;

	vector<vector<char>> board;
	Snake snake;
	FoodMenager foodMenager;

public:
	GameScene(sf::RenderWindow& gameWindow, SceneMenager* menag, LevelMenager& levelMenag)
	:sceneMenager(menag)
	,levelMenager(levelMenag)
	,menuBackGround(sf::Vector2f(gameWindow.getSize().x, gameWindow.getSize().y))
	,exitButton(buttonsFont)
	,scoreText(titleFont)
	,board(levelMenager.getLevelBoard())
	,snake(levelMenag.getSnakeCordsAtStart()[0], levelMenag.getSnakeCordsAtStart()[1], levelMenag.getSnakeDirectionAtStart())
	,foodMenager(board)
	{
		if (!titleFont.openFromFile("Fonts/blocked.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}
		if (!buttonsFont.openFromFile("Fonts/blocks.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}
		if (!headTexture.loadFromFile("Textures/SnakeTextures/Face.png")) {
			cout << "Blad w ladowaniu tekstury glowy" << "\n";
		}

		menuBackGround.setPosition(sf::Vector2f(0, 0));
		menuBackGround.setFillColor(sf::Color(0, 0, 0, 245));

		exitButton.setFont(buttonsFont);
		exitButton.setString(">EXIT");
		exitButton.setCharacterSize(60);
		exitButton.setFillColor(sf::Color::White);
		pauseMenuButtons.push_back(&exitButton);

		for (sf::Text* btn : pauseMenuButtons) {
			pauseMenuButtonHeight += btn->getLocalBounds().size.y;
		}
		pauseMenuButtonHeight += pauseMenuButtonSpacing * (pauseMenuButtons.size() - 1);

		scoreText.setFont(titleFont);
		scoreText.setCharacterSize(90);
		scoreText.setFillColor(sf::Color::Yellow);

		heightOfBoard = boardMarginY + ((boardBlockMargin + boardBlockSize) * board.size());
	}

	void eventHandler(sf::Event event, sf::RenderWindow& gameWindow) override {

		if (event.is<sf::Event::MouseMoved>()) {
			if (exitButton.getFillColor() == sf::Color::White
				&& exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				exitButton.setString("> EXIT");
				exitButton.setFillColor(sf::Color::Red);
			}
			else if (exitButton.getFillColor() == sf::Color::Red
				&& !exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				exitButton.setString(">EXIT");
				exitButton.setFillColor(sf::Color::White);
			}
		}

		if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				sceneMenager->loadLevelSelectScene();
			}
		}

		if (auto key = event.getIf<sf::Event::KeyPressed>()) {

			if (key->code == sf::Keyboard::Key::Escape) {
				if (isPaused == true) {
					isPaused = false;
				}
				else {
					isPaused = true;
				}
			}


			snake.snakeDirectionChange(*key);
		}
	}

	void update(float deltaTime) override {

		if (isPaused == false) {
			snake.snakeMove(deltaTime, board, foodMenager);
			snake.updateEffects(deltaTime);

			if (snake.getStatus() == true) {
				foodMenager.foodGenerate(deltaTime);
			}
		}

	}
		
	void render(sf::RenderWindow& gameWindow) {
		renderCurrentBoardState(gameWindow);
		snakeRender(gameWindow);
		foodRender(gameWindow);
		scoreRender(gameWindow);
		effectTimerRender(gameWindow);


		if(isPaused == true){
			pauseMenuRender(gameWindow);
		}
	}

	void renderCurrentBoardState(sf::RenderWindow& gameWindow) {
		sf::RectangleShape block(sf::Vector2f(boardBlockSize, boardBlockSize));
		block.setFillColor(boardWallColor);

		for (int y = 0; y < board.size(); y++) {
			for (int x = 0; x < board[y].size(); x++)
			{
				if (board[y][x] == '#') {
					block.setPosition(sf::Vector2f(boardMarginX + (x * (boardBlockMargin + boardBlockSize)), boardMarginY + (y * (boardBlockMargin + boardBlockSize))));
					gameWindow.draw(block);
				}
			}
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

	void foodRender(sf::RenderWindow& gameWindow) {
		std::vector<std::unique_ptr<Food>>& foodCords= foodMenager.getFoodCoordinates();
		for (std::unique_ptr<Food>& food : foodCords) {
			sf::Sprite foodSprite(food->getTexture());
			foodSprite.setTextureRect(sf::IntRect({ 0,0 }, { 32, 32 }));
			foodSprite.setOrigin(sf::Vector2f(foodSprite.getGlobalBounds().getCenter().x, foodSprite.getGlobalBounds().getCenter().y));
			foodSprite.setScale(sf::Vector2f(static_cast<float>(boardBlockSize) / 32.f, static_cast<float>(boardBlockSize) / 32.f));
			foodSprite.setPosition(sf::Vector2f(boardMarginX + (food->getCoordinates()[0] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2), boardMarginY + (food->getCoordinates()[1] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2)));
			gameWindow.draw(foodSprite);
		}
	}

	void effectTimerRender(sf::RenderWindow& gameWindow) {
		sf::RectangleShape iconBlock(sf::Vector2f(effectBlockSize, effectBlockSize));
		iconBlock.setFillColor(sf::Color::Yellow);
		
		int effectIndexY = 0;
		for (auto& effect : snake.getEffects()) {
			if (effect.stackable == false) {
				iconBlock.setPosition(sf::Vector2f(effectMarginX , heightOfBoard + effectMarginY + ((effectBlockMargin+effectBlockSize)*effectIndexY)));

				sf::Sprite foodIcon(effect.food->getTexture());
				foodIcon.setTextureRect(sf::IntRect({ 0,0 }, { 32, 32 }));
				foodIcon.setScale(sf::Vector2f((iconBlock.getSize().x-4.f)/ 32.f, (iconBlock.getSize().y-4.f) / 32.f));
				foodIcon.setPosition(sf::Vector2f(iconBlock.getPosition().x + 2, iconBlock.getPosition().y + 2));

				gameWindow.draw(iconBlock);
				gameWindow.draw(foodIcon);
				
				double timeInPercent = (effect.remainingTime / effect.food->getEffectDurration()) * 100.0;

				for (int i = 1; i <= 10; i++)
				{
					sf::RectangleShape timerBlock(sf::Vector2f(effectBlockSize-4, effectBlockSize-4));
					timerBlock.setFillColor(effectTimerColor);
					timerBlock.setPosition(sf::Vector2f(effectMarginX + ((effectBlockSize + effectBlockMargin) * i) + 2, heightOfBoard + effectMarginY + ((effectBlockSize + effectBlockMargin) * effectIndexY) + 2));

					if (timeInPercent < i * 10) {
						timerBlock.setSize(sf::Vector2f(timerBlock.getSize().x * fmod(timeInPercent, 10.0) / 10.0f, timerBlock.getSize().y));
						gameWindow.draw(timerBlock);
						break;
					}
					else {
						gameWindow.draw(timerBlock);
					}
				}
			}
			else {

			}
			effectIndexY++;
		}
	}

	void scoreRender(sf::RenderWindow& gameWindow) {
		scoreText.setString("Score: " + std::to_string(snake.getScore()));
		scoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - scoreText.getLocalBounds().size.x) - 30.0, 0.0));
		gameWindow.draw(scoreText);
	}

	void pauseMenuRender(sf::RenderWindow& gameWindow) {
		gameWindow.draw(menuBackGround);

		double addedHeight = -60;                   //tylko dla testu naprawiæ potem nwm czemu ale btn s¹ przesuniete w dó³ o oko³o 60
		for (sf::Text* btn : pauseMenuButtons) {
			btn->setPosition(sf::Vector2f((gameWindow.getSize().x - btn->getLocalBounds().size.x)/2 , (gameWindow.getSize().y - pauseMenuButtonHeight + addedHeight) / 2));
			addedHeight += btn->getLocalBounds().size.y + pauseMenuButtonSpacing;
			gameWindow.draw(*btn);
		}
	}

};

