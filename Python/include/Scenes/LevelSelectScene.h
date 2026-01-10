#pragma once
#include "Scenes/Scene.h"
#include "Menagers/SceneMenager.h"
#include "Menagers/LevelMenager.h"

#include <vector>
#include <filesystem>
#include <string>

using namespace std;

class LevelSelectScene : public Scene
{
private:
	SceneMenager* sceneMenager;  
	LevelMenager& levelMenager;
	int currentLevelIndex = 0;
	int currentLevelBestScore = 0;

	bool showErrorDialog = false;
	string errorMessage = "";
	sf::RectangleShape dialogBackground;
	sf::RectangleShape errorDialogBox;
	sf::Text errorText;
	sf::Text errorDialogExit;

	sf::Text bestScoreText;

	sf::Font titleFont;
	sf::Font buttonsFont;
	sf::Text titleText;
	sf::Text playBtn;
	sf::Text nextLevelBtn;
	sf::Text previousLevelBtn;
	sf::Text selectedLevelText;
	sf::Text backBtn;
	sf::Text addLevelBtn;
	sf::Text removeLevelBtn;

public:
	LevelSelectScene(sf::RenderWindow& gameWindow, SceneMenager* menag, LevelMenager& levelMenager)
		:sceneMenager(menag) 
		,levelMenager(levelMenager)
		,dialogBackground(sf::Vector2f(gameWindow.getSize().x, gameWindow.getSize().y))
		,errorDialogBox(sf::Vector2f(650.0, 350.0))
		,errorText(titleFont)
		,errorDialogExit(buttonsFont)
		,bestScoreText(titleFont)
		,titleText(titleFont)
		,playBtn(buttonsFont)
		,nextLevelBtn(buttonsFont)
		,previousLevelBtn(buttonsFont)
		,selectedLevelText(buttonsFont)
		,backBtn(buttonsFont)
		,addLevelBtn(buttonsFont)
		,removeLevelBtn(buttonsFont)
	{

		if (!titleFont.openFromFile("Fonts/blocked.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}
		if (!buttonsFont.openFromFile("Fonts/blocks.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}

		dialogBackground.setPosition(sf::Vector2f(0, 0));
		dialogBackground.setFillColor(sf::Color(0, 0, 0, 220));

		errorDialogBox.setPosition(sf::Vector2f( (gameWindow.getSize().x - errorDialogBox.getLocalBounds().size.x)/2 , (gameWindow.getSize().y - errorDialogBox.getLocalBounds().size.y) / 2));
		errorDialogBox.setFillColor(sf::Color(40, 40, 40));
		errorDialogBox.setOutlineColor(sf::Color::Red);
		errorDialogBox.setOutlineThickness(4);

		errorText.setFont(titleFont);
		errorText.setString("");
		errorText.setCharacterSize(30);
		errorText.setFillColor(sf::Color::Red);
		errorText.setPosition(sf::Vector2f( errorDialogBox.getPosition().x + 15, errorDialogBox.getPosition().y + 30));

		errorDialogExit.setFont(buttonsFont);
		errorDialogExit.setString("X");
		errorDialogExit.setCharacterSize(80);
		errorDialogExit.setFillColor(sf::Color::White);
		errorDialogExit.setPosition(sf::Vector2f(errorDialogBox.getPosition().x + errorDialogBox.getLocalBounds().size.x - errorDialogExit.getLocalBounds().size.x-15 , errorDialogBox.getPosition().y - 40));

		titleText.setFont(titleFont);
		titleText.setString("Select Your Level");
		titleText.setCharacterSize(90);
		titleText.setFillColor(sf::Color::Green);
		titleText.setPosition(sf::Vector2f((gameWindow.getSize().x - titleText.getLocalBounds().size.x) / 2, 40.0));

		bestScoreText.setFont(titleFont);
		bestScoreText.setString("Personal Best: " + std::to_string(levelMenager.getBestScoreFromJson()));
		bestScoreText.setCharacterSize(45);
		bestScoreText.setFillColor(sf::Color::Yellow);
		bestScoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - bestScoreText.getLocalBounds().size.x) / 2, gameWindow.getSize().y-bestScoreText.getGlobalBounds().size.y-25 ));

		nextLevelBtn.setFont(buttonsFont);
		nextLevelBtn.setString(">");
		nextLevelBtn.setCharacterSize(160);
		nextLevelBtn.setFillColor(sf::Color::Green);
		nextLevelBtn.setPosition(sf::Vector2f(gameWindow.getSize().x - nextLevelBtn.getLocalBounds().size.x - 50.0, 240.0));

		previousLevelBtn.setFont(buttonsFont);
		previousLevelBtn.setString("<");
		previousLevelBtn.setCharacterSize(160);
		previousLevelBtn.setFillColor(sf::Color::Green);
		previousLevelBtn.setPosition(sf::Vector2f(50.0, 240.0));

		selectedLevelText.setFont(buttonsFont);
		selectedLevelText.setString(levelMenager.getCurrentLevelName());
		selectedLevelText.setCharacterSize(180);
		selectedLevelText.setFillColor(sf::Color::Yellow);
		selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, 200.0));

		backBtn.setFont(buttonsFont);
		backBtn.setString("<BACK");
		backBtn.setCharacterSize(80);
		backBtn.setFillColor(sf::Color::White);
		backBtn.setPosition(sf::Vector2f(30.0, (gameWindow.getSize().y - backBtn.getLocalBounds().size.y - backBtn.getLocalBounds().position.y - 20)));

		playBtn.setFont(buttonsFont);
		playBtn.setString("PLAY");
		playBtn.setCharacterSize(100);
		playBtn.setFillColor(sf::Color::White);
		playBtn.setPosition(sf::Vector2f((gameWindow.getSize().x - playBtn.getLocalBounds().size.x) / 2, 380.0));

		addLevelBtn.setFont(buttonsFont);
		addLevelBtn.setString("ADD>");
		addLevelBtn.setCharacterSize(80);
		addLevelBtn.setFillColor(sf::Color::White);
		addLevelBtn.setPosition(sf::Vector2f( (gameWindow.getSize().x - addLevelBtn.getLocalBounds().size.x - -addLevelBtn.getLocalBounds().position.x - 30), (gameWindow.getSize().y - addLevelBtn.getLocalBounds().size.y - addLevelBtn.getLocalBounds().position.y - 70 ) ));

		removeLevelBtn.setFont(buttonsFont);
		removeLevelBtn.setString("REMOVE>");
		removeLevelBtn.setCharacterSize(80);
		removeLevelBtn.setFillColor(sf::Color::White);
		removeLevelBtn.setPosition(sf::Vector2f( (gameWindow.getSize().x - removeLevelBtn.getLocalBounds().size.x - removeLevelBtn.getLocalBounds().position.x - 30), (gameWindow.getSize().y - removeLevelBtn.getLocalBounds().size.y - removeLevelBtn.getLocalBounds().position.y - 20)) );

	}

	void eventHandler(sf::Event event, sf::RenderWindow& gameWindow) override {

		if (event.is<sf::Event::MouseMoved>()) {

			if (showErrorDialog == false) {
				buttonHoverEffect(backBtn, gameWindow, sf::Color::White, sf::Color::Red, "<BACK", "< BACK");
				buttonHoverEffect(playBtn, gameWindow, sf::Color::White, sf::Color::Green, "PLAY", "> PLAY <", 1);
				buttonHoverEffect(addLevelBtn, gameWindow, sf::Color::White, sf::Color::Green, "ADD>", "ADD >", 2);
				buttonHoverEffect(removeLevelBtn, gameWindow, sf::Color::White, sf::Color::Red, "REMOVE>", "REMOVE >", 2);
				buttonHoverEffect(nextLevelBtn, gameWindow, sf::Color::Green, sf::Color::Yellow, ">", ">");
				buttonHoverEffect(previousLevelBtn, gameWindow, sf::Color::Green, sf::Color::Yellow, "<", "<");
			}
			else {
				buttonHoverEffect(errorDialogExit, gameWindow, sf::Color::White, sf::Color::Red, "X", "X");
			}

		}

		if (showErrorDialog == false) {


			if (buttonClicked(nextLevelBtn, gameWindow, event)) {
				levelMenager.nextLevel();
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				bestScoreText.setString("Personal Best: " + std::to_string(levelMenager.getBestScoreFromJson()));

				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
				bestScoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - bestScoreText.getLocalBounds().size.x) / 2, bestScoreText.getPosition().y));
			}

			else if(buttonClicked(previousLevelBtn, gameWindow, event)) {
				levelMenager.previousLevel();
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				bestScoreText.setString("Personal Best: " + std::to_string(levelMenager.getBestScoreFromJson()));
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
				bestScoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - bestScoreText.getLocalBounds().size.x) / 2, bestScoreText.getPosition().y));
			}

			else if (buttonClicked(backBtn, gameWindow, event)) {

				sceneMenager->loadMainMenu();
			}

			else if (buttonClicked(playBtn, gameWindow, event)) {
				if (!levelMenager.isLevelListEmpty()) {
					sceneMenager->loadGameScene();
				}
			}

			else if (buttonClicked(removeLevelBtn, gameWindow, event)) {
			
				levelMenager.removeCurrentLevel();
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				bestScoreText.setString("Personal Best: " + std::to_string(levelMenager.getBestScoreFromJson()));

				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
				bestScoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - bestScoreText.getLocalBounds().size.x) / 2, bestScoreText.getPosition().y));
			}

			else if (buttonClicked(addLevelBtn, gameWindow, event)) {
				try {
					levelMenager.addNewLevel();
				}
				catch (const std::exception& e) {
					showErrorDialog = true;
					errorMessage = e.what();
				}
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				bestScoreText.setString("Personal Best: " + std::to_string(levelMenager.getBestScoreFromJson()));
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
				bestScoreText.setPosition(sf::Vector2f((gameWindow.getSize().x - bestScoreText.getLocalBounds().size.x) / 2, bestScoreText.getPosition().y));
			}


		}
		else {

			if (buttonClicked(errorDialogExit, gameWindow, event)) {
				showErrorDialog = false;
				errorMessage = "";
			}

		}
	}

	void update(float deltaTime) override {}

	void render(sf::RenderWindow& gameWindow) override {
		gameWindow.draw(titleText);
		gameWindow.draw(bestScoreText);
		gameWindow.draw(nextLevelBtn);
		gameWindow.draw(previousLevelBtn);
		gameWindow.draw(selectedLevelText);
		gameWindow.draw(backBtn);
		gameWindow.draw(playBtn);
		gameWindow.draw(addLevelBtn);
		gameWindow.draw(removeLevelBtn);
		
		if(showErrorDialog) {
			fileErrorDialogRender(gameWindow, errorMessage);
		}
	}

	void fileErrorDialogRender(sf::RenderWindow& gameWindow, string errorMessage) {
		gameWindow.draw(dialogBackground);
		gameWindow.draw(errorDialogBox);
		errorText.setString("Blad: \n" + errorMessage);
		gameWindow.draw(errorText);
		gameWindow.draw(errorDialogExit);
	}
};

