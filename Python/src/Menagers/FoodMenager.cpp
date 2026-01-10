#include "Menagers/FoodMenager.h"
#include <random>
#include <vector>
#include <array>

#include "Entities/Food.h"

FoodMenager::FoodMenager(std::vector<std::vector<char>> board)
	: randGen(randDevice()) 
{
	foodTypes.push_back({ []() {return new BasicFood(); }, BasicFood::rngWeight});
	foodTypes.push_back({ []() {return new SpicyFood(); }, SpicyFood::rngWeight});
	foodTypes.push_back({ []() {return new ReverserFood(); }, ReverserFood::rngWeight });
	foodTypes.push_back({ []() {return new CuttingFood(); }, CuttingFood::rngWeight });
	foodTypes.push_back({ []() {return new GodFood(); }, GodFood::rngWeight });
	foodTypes.push_back({ []() {return new BlindingFood(); }, BlindingFood::rngWeight });

	for (FoodType& type : foodTypes) {
		weightSum += type.weight;
	}

	for (int y = 0; y < board.size(); y++) {
		for (int x = 0; x < board[y].size(); x++) {
			if (board[y][x] != '#' && board[y][x] != 'S' && board[y][x] != 's') { this->addEmptyLocation(x, y); }
		}
	}
}

void FoodMenager::foodGenerate(float deltaTime) {
	foodGenerationTimer += deltaTime;

	if (foodGenerationTimer < foodMaxGenerationTime || emptyLocations.empty()) { return; }

	std::cout << "Sumaaaaaaaaaaaaaaaaaaaaaaaaaaaa: " << weightSum << "\n";
	std::uniform_int_distribution<> dist(1, weightSum);
	int random = dist(randGen);

	std::uniform_int_distribution<> randGenertedPos(0, emptyLocations.size() - 1);
	int randomPos = randGenertedPos(randGen);
	int x = emptyLocations.at(randomPos)[0];
	int y = emptyLocations.at(randomPos)[1];
	this->removeEmptyLocation(x, y);

	int currentWeightSum = 0;
	for (FoodType food : foodTypes) {
		currentWeightSum += food.weight;

		if (random <= currentWeightSum) {
			std::unique_ptr<Food> newFood(food.foodFactory());
			newFood->setCoordinates(x,y);
			std::cout << "Wygenerowal: " << newFood->getCoordinates()[0] << " " << newFood->getCoordinates()[1] << "\n";
			foodCoordinates.push_back(std::move(newFood));
			break;
		}
	}

	foodGenerationTimer = 0.0f;
}

void FoodMenager::addEmptyLocation(int x, int y) {
	emptyLocations.push_back(std::array<int, 2>{x, y});
}

void FoodMenager::removeEmptyLocation(int x, int y) {
	emptyLocations.erase(std::remove(emptyLocations.begin(), emptyLocations.end(), std::array<int, 2>{x, y}), emptyLocations.end());
}

std::vector<std::unique_ptr<Food>>& FoodMenager::getFoodCoordinates(){
	return foodCoordinates;
}


