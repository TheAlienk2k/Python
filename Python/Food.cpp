#include "Food.h"
#include "Snake.h"
#include <iostream>

BasicFood::BasicFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;
	effectDurration = 0.f;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Textures/FoodTextures/basicFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury BasicFood \n"; }
		isLoaded = true;
	}
	texture = &basicTexture;
}

void BasicFood::applyEffect(Snake& snake)
{
	snake.addScore(1);
}

void BasicFood::expireEffect(Snake& snake)
{
}

SpicyFood::SpicyFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;
	effectDurration = 10.f;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Textures/FoodTextures/spicyFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury spicyFood \n"; }
		isLoaded = true;
	}
	texture = &basicTexture;
}

void SpicyFood::applyEffect(Snake& snake)
{
	snake.addScore(1);
	snake.setMaxMoveTime(snake.getMaxMoveTime() - 0.025f);
}

void SpicyFood::expireEffect(Snake& snake)
{
	snake.setMaxMoveTime(snake.getMaxMoveTime() + 0.025f);
}