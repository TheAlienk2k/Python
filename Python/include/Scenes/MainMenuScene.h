#pragma once
#include "Scenes/Scene.h"
#include "Menagers/SceneMenager.h"

using namespace std;

class MainMenuScene : public Scene{

private:
	SceneMenager* menager;

	sf::Font titleFont;
	sf::Font buttonsFont;
	sf::Text titleText;
	sf::Text soloPlayBtn;
	sf::Text multiPlayBtn;


public:
	MainMenuScene(sf::RenderWindow &gameWindow, SceneMenager* menag)
		: menager(menag)
		, titleText(titleFont)             //sprawdziæ jak to zrobiæ bo czcionka jest ³adowana przed jej wczytaniem z pliku
		, soloPlayBtn(buttonsFont)         //w teori zawsze zadzia³a ale lepiej to poprawiæ
		, multiPlayBtn(buttonsFont)
	    {

		if (!titleFont.openFromFile("Assets/Fonts/blocked.ttf")) {
			cout<<"Blad w ladowaniu czcionki" << "\n";
		}
		if (!buttonsFont.openFromFile("Assets/Fonts/blocks.ttf")) {
			cout << "Blad w ladowaniu czcionki" << "\n";
		}

		titleText.setFont(titleFont);
		titleText.setString("Python");
		titleText.setCharacterSize(120);
		titleText.setFillColor(sf::Color::Green);
		titleText.setPosition(sf::Vector2f((gameWindow.getSize().x - titleText.getLocalBounds().size.x)/2, 50.0));

		soloPlayBtn.setFont(buttonsFont);
		soloPlayBtn.setString(">Singleplayer");
		soloPlayBtn.setCharacterSize(70);
		soloPlayBtn.setFillColor(sf::Color::White);
		soloPlayBtn.setPosition(sf::Vector2f((gameWindow.getSize().x - soloPlayBtn.getLocalBounds().size.x) / 2, 210.0));

		multiPlayBtn.setFont(buttonsFont);
		multiPlayBtn.setString(">Multiplayer");
		multiPlayBtn.setCharacterSize(70);
		multiPlayBtn.setFillColor(sf::Color::Red);
		multiPlayBtn.setPosition(sf::Vector2f((gameWindow.getSize().x - soloPlayBtn.getLocalBounds().size.x) / 2, 280.0));
	}

	void eventHandler(sf::Event event, sf::RenderWindow &gameWindow) override {

		if (event.is<sf::Event::MouseMoved>()) {
			buttonHoverEffect(soloPlayBtn, gameWindow, sf::Color::White, sf::Color::Green, ">Singleplayer", "> Singleplayer");
		}

		if (buttonClicked(soloPlayBtn, gameWindow, event)) {
			menager->loadLevelSelectScene();
		}
	}

	void update(float deltaTime) override {}

	void render(sf::RenderWindow &gameWindow) override{
		gameWindow.draw(titleText);
		gameWindow.draw(soloPlayBtn);
		gameWindow.draw(multiPlayBtn);
	}
};

