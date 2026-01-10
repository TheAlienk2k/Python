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
		if (!basicTexture.loadFromFile("Assets/Textures/FoodTextures/basicFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury BasicFood \n"; }
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
	effectDurration = 15.f;
	stackable = true;
	id = 2;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Assets/Textures/FoodTextures/spicyFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury spicyFood \n"; }
		std::cout << "Zaladowano texture spicysFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void SpicyFood::applyEffect(Snake& snake)
{                                             
	if (activeStacks < maxStacks)
	{
		snake.setMaxMoveTime(snake.getMaxMoveTime() - accelerationValue);
		activeStacks++;

		this->appliedSuccessfully = true;
	}
	else
	{
		this->appliedSuccessfully = false;
	}
}

void SpicyFood::expireEffect(Snake& snake)
{
	if (this->appliedSuccessfully)
	{
		snake.setMaxMoveTime(snake.getMaxMoveTime() + accelerationValue);
		activeStacks--;
	}
}





ReverserFood::ReverserFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;

	scoreValue = 10;
	effectDurration = 8.f;
	stackable = false;
	id = 3;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Assets/Textures/FoodTextures/lemonFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury ReverserFood \n"; }
		std::cout << "Zaladowano texture ReverserFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void ReverserFood::applyEffect(Snake& snake)
{
	snake.reverseControls(true);
}

void ReverserFood::expireEffect(Snake& snake)
{
	snake.reverseControls(false);
}





CuttingFood::CuttingFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;

	scoreValue = 1;
	effectDurration = 10.f;
	stackable = false;
	id = 4;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Assets/Textures/FoodTextures/mysteriousFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury CuttingFood \n"; }
		std::cout << "Zaladowano texture CuttingFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void CuttingFood::applyEffect(Snake& snake)
{
	snake.slicedSnake(true);
}

void CuttingFood::expireEffect(Snake& snake)
{
	snake.slicedSnake(false);
}





GodFood::GodFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;

	scoreValue = 5;
	effectDurration = 6.f;
	stackable = false;
	id = 5;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Assets/Textures/FoodTextures/godFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury GodFood \n"; }
		std::cout << "Zaladowano texture GodFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void GodFood::applyEffect(Snake& snake)
{
	snake.godMode(true);
}

void GodFood::expireEffect(Snake& snake)
{
	snake.godMode(false);
}





BlindingFood::BlindingFood(int x, int y)
{
	coordinates[0] = x;
	coordinates[1] = y;

	scoreValue = 7;
	effectDurration = 10.f;
	stackable = false;
	id = 6;

	static sf::Texture basicTexture;
	static bool isLoaded = false;

	if (!isLoaded)
	{
		if (!basicTexture.loadFromFile("Assets/Textures/FoodTextures/rottenFood.png")) { std::cout << "Blad: nie udalo sie wczytac tekstury BlindingFood \n"; }
		std::cout << "Zaladowano texture BlindingFood" << "\n";
		isLoaded = true;
	}
	texture = &basicTexture;
}

void BlindingFood::applyEffect(Snake& snake)
{
	snake.blinded(true);
}

void BlindingFood::expireEffect(Snake& snake)
{
	snake.blinded(false);
}