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

	std::optional<sf::RenderTexture> lightLayer;
	std::optional<sf::Sprite> lightSprite;
	bool isLightLayerCreated = false;
	
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
	int boardBlockSize = 32;
	int boardBlockMargin = 5;
	const int boardMarginX = 50;
	const int boardMarginY = 50;

	sf::Vector2f finalBoardSize;
	sf::Vector2f finalBoardPos;

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
	,lightLayer()
	,lightSprite{}
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
		if (!titleFont.openFromFile("Assets/Fonts/blocked.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}
		if (!buttonsFont.openFromFile("Assets/Fonts/blocks.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}
		if (!headTexture.loadFromFile("Assets/Textures/SnakeTextures/Face.png")) {
			cout << "Blad w ladowaniu tekstury glowy" << "\n";
		}

		boardScaling(gameWindow);

		menuBackGround.setPosition(sf::Vector2f(0, 0));
		menuBackGround.setFillColor(sf::Color(0, 0, 0, 245));

		pauseMenuHeader.setFont(titleFont);
		pauseMenuHeader.setString("PAUSE");
		pauseMenuHeader.setCharacterSize(160);
		pauseMenuHeader.setFillColor(sf::Color::Green);
		pauseMenuHeader.setPosition(sf::Vector2f((gameWindow.getSize().x - pauseMenuHeader.getLocalBounds().size.x) / 2, 10));

		resumePauseButton.setFont(buttonsFont);
		resumePauseButton.setString("RESUME");
		resumePauseButton.setCharacterSize(60);
		resumePauseButton.setFillColor(sf::Color::White);
		
		exitButton.setFont(buttonsFont);
		exitButton.setString("EXIT");
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
		playAgainButton.setString("PLAY AGAIN");
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
			buttonHoverEffect(exitButton, gameWindow, sf::Color::White, sf::Color::Red, "EXIT", ">EXIT<", 1);
			buttonHoverEffect(resumePauseButton, gameWindow, sf::Color::White, sf::Color::Green, "RESUME", ">RESUME<", 1);
			buttonHoverEffect(playAgainButton, gameWindow, sf::Color::White, sf::Color::Green, "PLAY AGAIN", ">PLAY AGAIN<", 1);
		}

		
		if (buttonClicked(exitButton, gameWindow, event)) {
			sceneMenager->loadLevelSelectScene();
		}
		else if (buttonClicked(playAgainButton, gameWindow, event)) {
			sceneMenager->loadGameScene();
		}
		else if (buttonClicked(resumePauseButton, gameWindow, event)) {
			isPaused = false;
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

		if (snake.isSnakeBlinded() == true) {
			renderSnakeBlindArea(gameWindow);
		}

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

		sf::RectangleShape boardWalls(finalBoardSize);
		boardWalls.setFillColor(sf::Color::Transparent);
		boardWalls.setOutlineColor(sf::Color::Yellow);
		boardWalls.setOutlineThickness(4);
		boardWalls.setPosition(finalBoardPos);

		gameWindow.draw(boardWalls);

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

		if(snake.isSnakeInGodMode() == false) {
			snakeBlock.setFillColor(snakeColor);
		}
		else {
			snakeBlock.setFillColor(sf::Color(200,200,0,200));
		}

		bool isHead = true;
		for (const std::array<int, 2>&cord : snake.getSnakeCords()) {
			snakeBlock.setPosition(sf::Vector2f(
				boardMarginX + (cord[0] * (boardBlockMargin + boardBlockSize)),
				boardMarginY + (cord[1] * (boardBlockMargin + boardBlockSize))
			));
			gameWindow.draw(snakeBlock);

			if (isHead) {
				sf::Sprite snakeHead(headTexture);
				snakeHead.setTextureRect(sf::IntRect({ 0,0 }, { 32, 32 }));
				snakeHead.setOrigin(sf::Vector2f(16.f, 16.f));

				float scale = static_cast<float>(boardBlockSize) / 32.f;
				snakeHead.setScale(sf::Vector2f(scale, scale));

				float posX = boardMarginX + (cord[0] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2.f);
				float posY = boardMarginY + (cord[1] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2.f);
				snakeHead.setPosition(sf::Vector2f(posX, posY));

				sf::Vector2i actualDir = snake.getLastActualDirection();

				if (actualDir.x == 1)      snakeHead.setRotation(sf::degrees(90.f));  // prawo
				else if (actualDir.x == -1) snakeHead.setRotation(sf::degrees(270.f)); // lewo
				else if (actualDir.y == 1)  snakeHead.setRotation(sf::degrees(180.f)); // do³
				else if (actualDir.y == -1) snakeHead.setRotation(sf::degrees(0.f));   // gora

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

	void boardScaling(sf::RenderWindow& gameWindow) {
		float maxBoardW = gameWindow.getSize().x * 0.60f; //max % szerokoœci okna
		float maxBoardH = gameWindow.getSize().y * 0.60f; //max % d³ugoœæ okna

		int cols = board[0].size();
		int rows = board.size();

		float sizeByWidth = (maxBoardW + boardBlockMargin) / cols - boardBlockMargin;
		float sizeByHeight = (maxBoardH + boardBlockMargin) / rows - boardBlockMargin;

		boardBlockSize = std::min(sizeByWidth, sizeByHeight);

		if (boardBlockSize < 1.0f) boardBlockSize = 1.0f;

		finalBoardSize = sf::Vector2f(
			cols * (boardBlockSize + boardBlockMargin) - boardBlockMargin,
			rows * (boardBlockSize + boardBlockMargin) - boardBlockMargin
		);
		finalBoardPos = sf::Vector2f(boardMarginX, boardMarginY);
	}

	void renderSnakeBlindArea(sf::RenderWindow& gameWindow) {
		if (!isLightLayerCreated) {
			lightLayer.emplace(sf::Vector2u(
				static_cast<unsigned int>(finalBoardSize.x),
				static_cast<unsigned int>(finalBoardSize.y)
			));
			lightSprite.emplace(lightLayer->getTexture());
			isLightLayerCreated = true;
		}

		lightLayer->clear(sf::Color::Black);

		float posX = (snake.getSnakeCords().at(0)[0] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2.f);
		float posY = (snake.getSnakeCords().at(0)[1] * (boardBlockMargin + boardBlockSize)) + (boardBlockSize / 2.f);

		float baseRadius = boardBlockSize * 2.5f;
		int steps = 15;

		for (int i = steps; i > 0; --i) {
			float r = baseRadius * (1.0f + (float)i / steps);
			sf::CircleShape lightCircle(r);
			lightCircle.setOrigin({ r, r });
			lightCircle.setPosition({ posX, posY });

			int alphaValue = 255 - (255 * (steps - i) / steps);
			lightCircle.setFillColor(sf::Color(0, 0, 0, static_cast<uint8_t>(alphaValue)));
			lightLayer->draw(lightCircle, sf::BlendNone);
		}

		sf::CircleShape centerHole(baseRadius);
		centerHole.setOrigin({ baseRadius, baseRadius });
		centerHole.setPosition({ posX, posY });
		centerHole.setFillColor(sf::Color::Transparent);
		lightLayer->draw(centerHole, sf::BlendNone);

		lightLayer->display();

		if (lightSprite) {
			lightSprite->setPosition(finalBoardPos);
			gameWindow.draw(*lightSprite);
		}
	}
};

