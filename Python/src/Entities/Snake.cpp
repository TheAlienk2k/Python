#include "Entities/Snake.h"

#include <iostream>
#include <algorithm>
#include <utility>

#include "Entities/Food.h"
#include "Menagers/FoodMenager.h"

Snake::Snake(int x, int y, char direction)
{
	snakeBlocksCords.insert(snakeBlocksCords.begin(), std::array<int, 2>{x , y});
	currentDirection = direction;
}

void Snake::snakeDirectionChange(const sf::Event::KeyPressed& key) {
	if (isAlive == false) return;

	if ((key.code == sf::Keyboard::Key::W)) {
		if ((!inputQueue.empty() && inputQueue.size() <= inputQueueMaxSize && inputQueue.back() != 's')
			|| (inputQueue.empty() && currentDirection != 's')) {

			inputQueue.push('w');
		}
	}
	else if ((key.code == sf::Keyboard::Key::S)) {
		if ((!inputQueue.empty() && inputQueue.size() <= inputQueueMaxSize && inputQueue.back() != 'w')
			|| (inputQueue.empty() && currentDirection != 'w')) {

			inputQueue.push('s');
		}
	}
	else if(key.code == sf::Keyboard::Key::A) {
		if ((!inputQueue.empty() && inputQueue.size() <= inputQueueMaxSize && inputQueue.back() != 'd')
			|| (inputQueue.empty() && currentDirection != 'd')) {

			inputQueue.push('a');
		}
	}
	else if(key.code == sf::Keyboard::Key::D) {
		if ((!inputQueue.empty() && inputQueue.size() <= inputQueueMaxSize && inputQueue.back() != 'a')
			|| (inputQueue.empty() && currentDirection != 'a')) {

			inputQueue.push('d');
		}
	}
}

void Snake::snakeMove(float deltaTime, std::vector<std::vector<char>>& board, FoodMenager& foodMenager) {
	snakeMoveTimer += deltaTime;

	if (snakeMoveTimer < snakeMaxMoveTime || !isAlive) { return; }

		int snakeHeadX = snakeBlocksCords.at(0)[0];
		int snakeHeadY = snakeBlocksCords.at(0)[1];

		std::array<int, 2> directionChange;

		if(currentDirection == 'w') directionChange = {0, -1};
		else if (currentDirection == 's') directionChange = { 0, 1 };
		else if (currentDirection == 'a') directionChange = { -1, 0 };
		else if (currentDirection == 'd') directionChange = { 1, 0 };

		int newX = snakeHeadX + directionChange[0];
		int newY = snakeHeadY + directionChange[1];

		if (isValidMove(newX, newY, board)) {

			std::vector<std::unique_ptr<Food>>& foodCords = foodMenager.getFoodCoordinates();
			for (auto f = foodCords.begin(); f != foodCords.end(); f++) {
				Food* food = f->get();

				if (food->getCoordinates()[0] == newX && food->getCoordinates()[1] == newY) {
					this->snakeEat(std::move(*f));
					f = foodCords.erase(f);
					break;
				}
			}

			snakeBlocksCords.insert(snakeBlocksCords.begin(), { newX, newY });
			foodMenager.removeEmptyLocation(newX, newY);

			if (snakeBlocksCords.size() > snakeLength) {
				foodMenager.addEmptyLocation(snakeBlocksCords.back()[0], snakeBlocksCords.back()[1]);
				snakeBlocksCords.pop_back();
			}
		}
		else {
			snakeDeath();
		}

		if (!inputQueue.empty()) {
			currentDirection = inputQueue.front();
			inputQueue.pop();
		}

		snakeMoveTimer = 0.0f;
	
}

bool Snake::isValidMove(int &x, int &y, std::vector<std::vector<char>> &board) {

	if (x < 0) {
		x = board[y].size() - 1;
	}
	else if (x > board[y].size()-1) {
		x = 0;
	}

	if (y < 0) {
		y = board.size() - 1;
	}
	else if (y > board.size() - 1) {
		y = 0;
	}

	if (board[y][x] == '#') return false;

	auto it = std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array<int,2>{ x, y });
	return (it == snakeBlocksCords.end());
}

void Snake::snakeDeath() {
	isAlive = false;

	std::queue<char> emptyQueue;
	std::swap(inputQueue, emptyQueue);
}

bool Snake::getStatus() {
	return isAlive;
}

void Snake::snakeEat(std::unique_ptr<Food> food) {
	float duration = food->getEffectDurration();
	bool stackable = food->isStackable();
	int id = food->getId();

	snakeLength++;
	this->addScore(food.get()->getScoreValue());

	if (duration == 0.f) {
		food->applyEffect(*this);
		return;
	}

	if (duration > 0.f) {

		if (stackable == false) {
			if (currentEffects.count(id)) {
				if (!currentEffects.at(id).empty()) {
					currentEffects.at(id).begin()->remainingTime = duration;
					return; 
				}
			}
		}

		food->applyEffect(*this);
		currentEffects[id].emplace_back(ActiveEffect{ std::move(food), duration, stackable});
	}
}

void Snake::updateEffects(float deltaTime) {
	if (!isAlive) { return; }


	for (auto it = currentEffects.begin(); it != currentEffects.end(); ) {
		std::vector<ActiveEffect>& effects = it->second;

		for (int i = effects.size() - 1; i >= 0; --i) {
			effects[i].remainingTime -= deltaTime;

			if (effects[i].remainingTime <= 0) {
				effects[i].food->expireEffect(*this);
				effects.erase(effects.begin() + i);
			}
		}

		if (effects.empty()) {
			it = currentEffects.erase(it);
		}
		else {
			it++;
		}
	}
}

std::unordered_map<int, std::vector<ActiveEffect>>& Snake::getEffects() {
	return currentEffects;
}

void Snake::snakeVomit() {
	snakeLength--;
}

void Snake::addScore(int amount) {
	score += amount;

	std::cout << "Obecny wynik to: " << score << "\n";
}

int Snake::getScore() {
	return score;
}

char Snake::getDirection() {
	return currentDirection;
}

const std::vector<std::array<int, 2>>& Snake::getSnakeCords() const{
	return snakeBlocksCords;
}

float Snake::getMaxMoveTime() {
	return snakeMaxMoveTime;
}

void Snake::setMaxMoveTime(float maxTime) {
	snakeMaxMoveTime = maxTime;
}
