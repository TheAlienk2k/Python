#pragma once
#include "Scene.h"
#include "SceneMenager.h"
#include "LevelMenager.h"

#include <vector>
#include <filesystem>
#include <string>

using namespace std;

class LevelSelectScene : public Scene
{
private:
	SceneMenager* menager;
	vector<string> levelArray;
	int currentLevelIndex = 0;


	sf::Font titleFont;
	sf::Font buttonsFont;
	sf::Text titleText;
	sf::Text nextLevelBtn;
	sf::Text previousLevelBtn;
	sf::Text selectedLevelText;
	sf::Text backBtn;


public:
	LevelSelectScene(sf::RenderWindow& gameWindow, SceneMenager* menag)
		:menager(menag) 
		,titleText(titleFont)
		,nextLevelBtn(buttonsFont)
		,previousLevelBtn(buttonsFont)
		,selectedLevelText(buttonsFont)
		,backBtn(buttonsFont)
	{
		LevelMenager levelMenager("Levels");
		levelArray = levelMenager.getLevelNames();;

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
		selectedLevelText.setString(levelArray.at(currentLevelIndex));
		selectedLevelText.setCharacterSize(180);
		selectedLevelText.setFillColor(sf::Color::Yellow);
		selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, 200.0));

		backBtn.setFont(buttonsFont);
		backBtn.setString("<BACK");
		backBtn.setCharacterSize(100);
		backBtn.setFillColor(sf::Color::White);
		backBtn.setPosition(sf::Vector2f(30.0, 650.0));

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
		}


		if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			
			if (nextLevelBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				if (currentLevelIndex == levelArray.size()-1) {
					currentLevelIndex = 0;
				}
				else {
					currentLevelIndex++;
				}
				selectedLevelText.setString(levelArray.at(currentLevelIndex));
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
			}
			else if (previousLevelBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				if (currentLevelIndex == 0) {
					currentLevelIndex = levelArray.size()-1;
				}
				else {
					currentLevelIndex--;
				}
				selectedLevelText.setString(levelArray.at(currentLevelIndex));
				selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, selectedLevelText.getPosition().y));
			}
			else if (backBtn.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				menager->loadMainMenu();
			}
		}

	}

	void render(sf::RenderWindow& gameWindow) {
		gameWindow.draw(titleText);
		gameWindow.draw(nextLevelBtn);
		gameWindow.draw(previousLevelBtn);
		gameWindow.draw(selectedLevelText);
		gameWindow.draw(backBtn);
	}
};

