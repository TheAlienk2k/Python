#include "Entities/Food.h"
#include "Entities/Snake.h"
#include <iostream>

BasicFood::BasicFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;

	scoreValue = 1;
	effectDurration = 0.f;
	stackable = false;
	id = 1;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Textures/FoodTextures/basicFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury BasicFood \n"; }
		std::cout << "Zaladowano texture basicFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void BasicFood::applyEffect(Snake& snake)
{
}

void BasicFood::expireEffect(Snake& snake)
{
}




SpicyFood::SpicyFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;
	
	scoreValue = 3;
	effectDurration = 10.f;
	stackable = true;
	id = 2;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Textures/FoodTextures/spicyFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury spicyFood \n"; }
		std::cout << "Zaladowano texture spicysFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void SpicyFood::applyEffect(Snake& snake)
{                                             
	snake.setMaxMoveTime(snake.getMaxMoveTime() - 0.02f);
}

void SpicyFood::expireEffect(Snake& snake)
{
	snake.setMaxMoveTime(snake.getMaxMoveTime() + 0.02f);
}