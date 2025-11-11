#include "FoodMenager.h"
#include <random>
#include <vector>
#include <array>
#include <functional>

#include "Food.h"


struct FoodMenager::FoodType {
	std::function<Food* ()> foodFactory; 
	int weight;
};

FoodMenager::FoodMenager() {
	foodTypes.push_back({ []() {return new BasicFood(); }, BasicFood::rngWeight });
	foodTypes.push_back({ []() {return new SpicyFood(); }, SpicyFood::rngWeight });

	for (FoodType& type : foodTypes) {
		weightSum += type.weight;
	}
}

void FoodMenager::foodGenerate(float deltaTime, std::vector<std::vector<char>> board, std::vector<std::array<int, 2>> snakeBlocksCords) {
	if (foodGenerationTimer >= 0.f) { return; }

	std::uniform_int_distribution<> dist(1, weightSum);
	int random = dist(randGen);

	/*do {   -------------------------------------------------------------------------tu koniec trzeba bedzie zrobiæ vektor wolnych pozycji i na nim losowaæ pomyœleæ jeszcze jak to optymalnie zrobiæ
		std::uniform_int_distribution<> rowDist(0, board.size() - 1);
		int y = rowDist(randGen);

		std::uniform_int_distribution<> colDist(0, board[y].size() - 1);
		int x = colDist(randGen);
	} while ();*/

	int currentWeightSum = 0;
	for (FoodType food : foodTypes) {
		currentWeightSum += food.weight;
		if (random < currentWeightSum) {             //pomyœleæ o tym jeszcze kiedyœ ale raczej dobrze
			Food* newFood = food.foodFactory();
			newFood->setCoordinates(3,3);
			foodCoordinates.push_back(newFood);
		}
	}
	foodGenerationTimer = foodMaxGenerationTime;
}


