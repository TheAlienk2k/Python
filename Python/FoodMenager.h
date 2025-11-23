#pragma once
#include <vector>
#include <array>
#include <random>
#include <functional>

#include "Food.h"

class FoodMenager
{
private:

	struct FoodType {
		std::function<Food*()> foodFactory;
		int weight;
	};

	std::vector<std::unique_ptr<Food>> foodCoordinates;		//jedzenie na mapie
	std::vector<FoodType> foodTypes;		//wszystkie rodzaje jedzenia

	std::vector<std::array<int, 2>> emptyLocations;

	std::random_device randDevice;
	std::mt19937 randGen;

	int weightSum = 0;
	const float foodMaxGenerationTime = 5.f;
	float foodGenerationTimer = 0.0f;


public:
	FoodMenager(std:: vector<std::vector<char>> board);
	
	void foodGenerate(float deltaTime);
	void addEmptyLocation(int x, int y);
	void removeEmptyLocation(int x, int y);
	std::vector<std::unique_ptr<Food>>& getFoodCoordinates();
};

