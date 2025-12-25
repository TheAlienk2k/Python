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

		titleText.setFont(titleFont);
		titleText.setString("Select Your Level");
		titleText.setCharacterSize(90);
		titleText.setFillColor(sf::Color::Green);
		titleText.setPosition(sf::Vector2f((gameWindow.getSize().x - titleText.getLocalBounds().size.x) / 2, 40.0));

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

			if (backBtn.getFillColor() == sf::Color::White
				&& backBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				backBtn.setString("< BACK");
				backBtn.setFillColor(sf::Color::Green);
			}
			else if (backBtn.getFillColor() == sf::Color::Green
				&& !backBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {

				backBtn.setString("<BACK");
				backBtn.setFillColor(sf::Color::White);
			}

			else if (playBtn.getFillColor() == sf::Color::White
				&& playBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				playBtn.setFillColor(sf::Color::Green);
			}
			else if (playBtn.getFillColor() == sf::Color::Green
				&& !playBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				playBtn.setFillColor(sf::Color::White);
			}

		}


		if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			
			if (nextLevelBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				levelMenager.nextLevel();
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
			}
			else if (previousLevelBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				levelMenager.previousLevel();
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
			}
			else if (backBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				sceneMenager->loadMainMenu();
			}
			else if (playBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				sceneMenager->loadGameScene();
			}
			else if (removeLevelBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				levelMenager.removeCurrentLevel();
				selectedLevelText.setString(levelMenager.getCurrentLevelName());
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
			}
		}
	}

	void update(float deltaTime) override {}

	void render(sf::RenderWindow& gameWindow) override {
		gameWindow.draw(titleText);
		gameWindow.draw(nextLevelBtn);
		gameWindow.draw(previousLevelBtn);
		gameWindow.draw(selectedLevelText);
		gameWindow.draw(backBtn);
		gameWindow.draw(playBtn);
		gameWindow.draw(addLevelBtn);
		gameWindow.draw(removeLevelBtn);
	}
};

