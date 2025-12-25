#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <queue>

class Food;
class FoodMenager;

struct ActiveEffect {
	std::unique_ptr<Food> food;
	float remainingTime;
	bool stackable;
};

class Snake
{
private:
	std::vector<std::array<int, 2>> snakeBlocksCords; //[0]-Xcords [1]-Ycords  PRZEROBIÆ KIEDYS NA STRUCT (dla czytelnoœci)
	std::unordered_map<int, std::vector<ActiveEffect>> currentEffects;

	int snakeLength = 3;
	bool isAlive = true;
	int score = 0;

	float snakeMaxMoveTime = 0.2f;
	float snakeMoveTimer = 0.0f;

	char currentDirection; //MA£E LITERY!!!! 'w'-góra 's'-dó³ 'a'-lewo 'd'-prawo
	const int inputQueueMaxSize = 1;
	std::queue<char> inputQueue;

public:
	Snake(int x, int y, char direction);

	void snakeDirectionChange(const sf::Event::KeyPressed& key);

	void snakeMove(float deltaTime, std::vector<std::vector<char>>& board, FoodMenager& foodMenager);

	bool isValidMove(int &x, int &y, std::vector<std::vector<char>>& board);

	void snakeDeath();

	bool getStatus();

	void snakeEat(std::unique_ptr<Food> food);

	void updateEffects(float deltaTime);

	std::unordered_map<int, std::vector<ActiveEffect>>& getEffects();

	void snakeVomit();

	void addScore(int amount);

	int getScore();

	char getDirection();

	const std::vector<std::array<int, 2>>& getSnakeCords() const;

	float getMaxMoveTime();

	void setMaxMoveTime(float maxTime);
};

