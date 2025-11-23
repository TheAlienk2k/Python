#include "Food.h"
#include "Snake.h"
#include <iostream>

BasicFood::BasicFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;

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
	stackable = false;              //Zmieniæ jak skoñcze testowaæ renderowanie timera effectów
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
	snake.addScore(3);                                              //Bug score sie nie dodaje dla niestackowalnego jedzenia trzeba rzdzieliæ logike efektów i wyniku ;(
	snake.setMaxMoveTime(snake.getMaxMoveTime() - 0.01f);
}

void SpicyFood::expireEffect(Snake& snake)
{
	snake.setMaxMoveTime(snake.getMaxMoveTime() + 0.01f);
}