#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace std;

class Scene {
public:
	virtual void eventHandler(sf::Event event, sf::RenderWindow& gameWindow) {};
	virtual void render(sf::RenderWindow& gameWindow) {};
	virtual void update(float deltaTime) {};

};

