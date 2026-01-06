#pragma once
#include "Scenes/Scene.h"
#include "Menagers/SceneMenager.h"
#include "Menagers/LevelMenager.h"
#include "Entities/Snake.h"
#include "Menagers/FoodMenager.h"
#include "Entities/Food.h"

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
	double pauseMenuButtonsHeight = 0;
	double gameOverMenuButtonsHeight = 0;
	double menuButtonSpacing = 60;

	sf::Text pauseMenuHeader;
	vector<sf::Text*> pauseMenuButtons;
	sf::Text resumePauseButton;
	sf::Text exitButton;

	sf::Text gameOverMenuHeader;
	sf::Text finalScoreText;
	vector<sf::Text*> gameOverMenuButtons;
	sf::Text playAgainButton;

	const sf::Color snakeColor  = sf::Color::Green;
	const sf::Color boardWallColor = sf::Color::White;
	const int boardBlockSize = 32;
	const int boardMarginX = 50;
	const int boardMarginY = 50;
	const int boardBlockMargin = 5;

	int heightOfBoard;
	const sf::Color effectTimerColor = sf::Color::Green;
	const int effectBlockSize = 52;
	const int effectMarginX = 70;
	const int effectMarginY = 50;
	const int effectBlockMargin = 4;

	bool isScoreSaved = false;
	bool isPaused = false;
	vector<vector<char>> board;
	Snake snake;
	FoodMenager foodMenager;

public:
	GameScene(sf::RenderWindow& gameWindow, SceneMenager* menag, LevelMenager& levelMenag)
	:sceneMenager(menag)
	,levelMenager(levelMenag)
	,menuBackGround(sf::Vector2f(gameWindow.getSize().x, gameWindow.getSize().y))
	,pauseMenuHeader(titleFont)
	,resumePauseButton(buttonsFont)
	,exitButton(buttonsFont)
	,scoreText(titleFont)
	,gameOverMenuHeader(titleFont)
	,finalScoreText(titleFont)
	,playAgainButton(buttonsFont)
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

		pauseMenuHeader.setFont(titleFont);
		pauseMenuHeader.setString("PAUSE");
		pauseMenuHeader.setCharacterSize(160);
		pauseMenuHeader.setFillColor(sf::Color::Green);
		pauseMenuHeader.setPosition(sf::Vector2f((gameWindow.getSize().x - pauseMenuHeader.getLocalBounds().size.x) / 2, 10));

		resumePauseButton.setFont(buttonsFont);
		resumePauseButton.setString(">RESUME");
		resumePauseButton.setCharacterSize(60);
		resumePauseButton.setFillColor(sf::Color::White);
		
		exitButton.setFont(buttonsFont);
		exitButton.setString(">EXIT");
		exitButton.setCharacterSize(60);
		exitButton.setFillColor(sf::Color::White);

		pauseMenuButtons.push_back(&resumePauseButton);
		pauseMenuButtons.push_back(&exitButton);
		for (sf::Text* btn : pauseMenuButtons) {
			pauseMenuButtonsHeight += btn->getLocalBounds().size.y;
		}
		pauseMenuButtonsHeight += menuButtonSpacing * (pauseMenuButtons.size() - 1);

		gameOverMenuHeader.setFont(titleFont);
		gameOverMenuHeader.setString("GAME OVER");
		gameOverMenuHeader.setCharacterSize(160);
		gameOverMenuHeader.setFillColor(sf::Color::Red);
		gameOverMenuHeader.setPosition(sf::Vector2f((gameWindow.getSize().x - gameOverMenuHeader.getLocalBounds().size.x) / 2, 10));

		finalScoreText.setFont(titleFont);
		finalScoreText.setString("Your Score:");
		finalScoreText.setCharacterSize(55);
		finalScoreText.setFillColor(sf::Color::Yellow);
		finalScoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - finalScoreText.getLocalBounds().size.x) / 2, 175));

		playAgainButton.setFont(buttonsFont);
		playAgainButton.setString(">PLAY AGAIN");
		playAgainButton.setCharacterSize(60);
		playAgainButton.setFillColor(sf::Color::White);

		gameOverMenuButtons.push_back(&playAgainButton);
		gameOverMenuButtons.push_back(&exitButton);
		for (sf::Text* btn : gameOverMenuButtons) {
			gameOverMenuButtonsHeight += btn->getLocalBounds().size.y;
		}
		gameOverMenuButtonsHeight += menuButtonSpacing * (gameOverMenuButtons.size() - 1);

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

			if (resumePauseButton.getFillColor() == sf::Color::White
				&& resumePauseButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				resumePauseButton.setString("> RESUME");
				resumePauseButton.setFillColor(sf::Color::Green);
			}
			else if (resumePauseButton.getFillColor() == sf::Color::Green
				&& !resumePauseButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				resumePauseButton.setString(">RESUME");
				resumePauseButton.setFillColor(sf::Color::White);
			}

			if (playAgainButton.getFillColor() == sf::Color::White
				&& playAgainButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				playAgainButton.setString("> PLAY AGAIN");
				playAgainButton.setFillColor(sf::Color::Green);
			}
			else if (playAgainButton.getFillColor() == sf::Color::Green
				&& !playAgainButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				playAgainButton.setString(">PLAY AGAIN");
				playAgainButton.setFillColor(sf::Color::White);
			}
		}

		if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (exitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				sceneMenager->loadLevelSelectScene();
			}

			else if (playAgainButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				sceneMenager->loadGameScene();
			}

			else if (resumePauseButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				isPaused = false;
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
			else {
				if (isScoreSaved == false) {
					levelMenager.saveScoreToJson(snake.getScore());
					isScoreSaved = true;
				}
			}
		}

	}
		
	void render(sf::RenderWindow& gameWindow) {
		renderCurrentBoardState(gameWindow);
		snakeRender(gameWindow);
		foodRender(gameWindow);
		scoreRender(gameWindow);
		effectTimerRender(gameWindow);

		if (snake.getStatus() == false) {
			gameOverMenuRender(gameWindow);
		}
		else if(isPaused == true){
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
		int effectIndex = 0;


		for (const auto& pair : snake.getEffects()) {
			int id = pair.first;       
			
			iconBlock.setPosition(sf::Vector2f(effectMarginX, heightOfBoard + effectMarginY + ((effectBlockMargin + effectBlockSize) * effectIndex)));

			sf::Sprite foodIcon(pair.second.at(0).food->getTexture());
			foodIcon.setTextureRect(sf::IntRect({ 0,0 }, { 32, 32 }));
			foodIcon.setScale(sf::Vector2f((iconBlock.getSize().x - 4.f) / 32.f, (iconBlock.getSize().y - 4.f) / 32.f));
			foodIcon.setPosition(sf::Vector2f(iconBlock.getPosition().x + 2, iconBlock.getPosition().y + 2));

			gameWindow.draw(iconBlock);
			gameWindow.draw(foodIcon);
			if (pair.second.at(0).stackable == true) {
				sf::Text foodCount(buttonsFont);
				foodCount.setString("x" + std::to_string(pair.second.size()));
				foodCount.setCharacterSize(35);
				foodCount.setFillColor(sf::Color::White);
				foodCount.setOutlineColor(sf::Color::Black);
				foodCount.setOutlineThickness(5);
				
				sf::FloatRect textRect = foodCount.getLocalBounds();

				// 2. Ustaw Origin na PRAWY DOLNY RÓG tekstu, u¿ywaj¹c .size.x i .size.y
				foodCount.setOrigin(sf::Vector2f(
					textRect.position.x + textRect.size.x,  // Origin X = Offset X + Szerokoœæ
					textRect.position.y + textRect.size.y   // Origin Y = Offset Y + Wysokoœæ
				));

				// 3. Ustaw Pozycjê na PRAWY DOLNY RÓG bloku iconBlock.
				// Dziêki Origin ustawionemu w kroku 2, tekst bêdzie idealnie przylega³.
				foodCount.setPosition(sf::Vector2f(
					iconBlock.getPosition().x + iconBlock.getSize().x,
					iconBlock.getPosition().y + iconBlock.getSize().y
				));

				gameWindow.draw(foodCount);
			}

			double timeInPercent = (pair.second.at(0).remainingTime / pair.second.at(0).food->getEffectDurration()) * 100.0;

			for (int i = 1; i <= 10; i++)
			{
				sf::RectangleShape timerBlock(sf::Vector2f(effectBlockSize - 4, effectBlockSize - 4));
				timerBlock.setFillColor(effectTimerColor);
				timerBlock.setPosition(sf::Vector2f(effectMarginX + ((effectBlockSize + effectBlockMargin) * i) + 2, heightOfBoard + effectMarginY + ((effectBlockSize + effectBlockMargin) * effectIndex) + 2));

				if (timeInPercent < i * 10) {
					timerBlock.setSize(sf::Vector2f(timerBlock.getSize().x * fmod(timeInPercent, 10.0) / 10.0f, timerBlock.getSize().y));
					gameWindow.draw(timerBlock);
					break;
				}
				else {
					gameWindow.draw(timerBlock);
				}

			}

			effectIndex++;
		}
	}

	void scoreRender(sf::RenderWindow& gameWindow) {
		scoreText.setString("Score: " + std::to_string(snake.getScore()));
		scoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - scoreText.getLocalBounds().size.x) - 30.0, 0.0));
		gameWindow.draw(scoreText);
	}

	void pauseMenuRender(sf::RenderWindow& gameWindow) {
		gameWindow.draw(menuBackGround);
		gameWindow.draw(pauseMenuHeader);

		double addedHeight = 0;
		for (sf::Text* btn : pauseMenuButtons) {
			btn->setPosition(sf::Vector2f((gameWindow.getSize().x - btn->getLocalBounds().size.x)/2 , (gameWindow.getSize().y - pauseMenuButtonsHeight + addedHeight) / 2));
			addedHeight += btn->getLocalBounds().size.y + menuButtonSpacing;
			gameWindow.draw(*btn);
		}
	}

	void gameOverMenuRender(sf::RenderWindow& gameWindow) {
		gameWindow.draw(menuBackGround);
		gameWindow.draw(gameOverMenuHeader);

		finalScoreText.setString("Your Score: " + std::to_string(snake.getScore()) );
		gameWindow.draw(finalScoreText);

		double addedHeight = 0;
		for (sf::Text* btn : gameOverMenuButtons) {
			btn->setPosition(sf::Vector2f((gameWindow.getSize().x - btn->getLocalBounds().size.x) / 2, (gameWindow.getSize().y - gameOverMenuButtonsHeight + addedHeight) / 2));
			addedHeight += btn->getLocalBounds().size.y + menuButtonSpacing;
			gameWindow.draw(*btn);
		}
	}

};

