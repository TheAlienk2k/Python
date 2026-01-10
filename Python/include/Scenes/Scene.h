#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace std;

class Scene {
public:
	virtual void eventHandler(sf::Event event, sf::RenderWindow& gameWindow) {};
	virtual void render(sf::RenderWindow& gameWindow) {};
	virtual void update(float deltaTime) {};

protected:
    void buttonHoverEffect(sf::Text& button, sf::RenderWindow& gameWindow, sf::Color basicColor, sf::Color hoveredColor, const string& basicText, const string& hoveredText, int centerType = 0) {
        sf::Vector2f mousePos = gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow));

        sf::Color targetColor = basicColor;
        const string* targetText = &basicText;

        if (button.getGlobalBounds().contains(mousePos)) {
            targetColor = hoveredColor;
            targetText = &hoveredText;
        }

        if (button.getFillColor() != targetColor || button.getString() != *targetText) {
            float rightEdge = button.getPosition().x + button.getGlobalBounds().size.x;

            button.setFillColor(targetColor);
            button.setString(*targetText);

            if (centerType == 1) {
                button.setPosition(sf::Vector2f((gameWindow.getSize().x - button.getGlobalBounds().size.x) / 2.f, button.getPosition().y));
            }
            else if (centerType == 2) {
                button.setPosition(sf::Vector2f(rightEdge - button.getGlobalBounds().size.x, button.getPosition().y));
            }
        }
    }

	bool buttonClicked(sf::Text& button, sf::RenderWindow& gameWindow, sf::Event& event) {
		if (event.is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (button.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(gameWindow).x, sf::Mouse::getPosition(gameWindow).y))) {
				return true;
			}
		}

		return false;
	}
};

