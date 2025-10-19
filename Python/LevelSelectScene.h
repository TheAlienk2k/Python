#pragma once
#include "Scene.h"
#include "SceneMenager.h"

using namespace std;

class LevelSelectScene : public Scene
{
private:
	SceneMenager* menager;

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
		selectedLevelText.setString("LEVEL 1");
		selectedLevelText.setCharacterSize(180);
		selectedLevelText.setFillColor(sf::Color::Yellow);
		selectedLevelText.setPosition(sf::Vector2f((gameWindow.getSize().x - selectedLevelText.getLocalBounds().size.x) / 2, 200.0));

		backBtn.setFont(buttonsFont);
		backBtn.setString("<BACK");
		backBtn.setCharacterSize(100);
		backBtn.setFillColor(sf::Color::Green);
		backBtn.setPosition(sf::Vector2f(30.0, 650.0));


	}

	void eventHandler(sf::Event event, sf::RenderWindow& gameWindow) override {

	}

	void render(sf::RenderWindow& gameWindow) {
		gameWindow.draw(titleText);
		gameWindow.draw(nextLevelBtn);
		gameWindow.draw(previousLevelBtn);
		gameWindow.draw(selectedLevelText);
		gameWindow.draw(backBtn);
	}
};

