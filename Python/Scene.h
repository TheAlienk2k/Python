#pragma once
#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace std;

class Scene {
public:
	virtual void eventHandler(sf::Event event, sf::RenderWindow &gameWindow) = 0;
	virtual void render(sf::RenderWindow &gameWindow) = 0;

};

