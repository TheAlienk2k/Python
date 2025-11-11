#pragma once
#include <vector>
#include <random>

#include "Food.h"

class FoodMenager
{
private:
	struct FoodType;
	std::vector<Food*> foodCoordinates{};
	std::vector<FoodType> foodTypes{};

	std::random_device randDevice;
	std::mt19937 randGen;

	int weightSum = 0;
	float foodMaxGenerationTime = 15.f;
	float foodGenerationTimer = 0.f;


public:
	FoodMenager() :randGen(randDevice()) {};
	
	void foodGenerate(float deltaTime, std::vector<std::vector<char>> board, std::vector<std::array<int, 2>> snakeBlocksCords);
	std::vector<std::unique_ptr<Food>>& getFoodCoordinates() const;
};

