#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <queue>

class Food;

class Snake
{
private:
	std::vector<std::array<int, 2>> snakeBlocksCords; //[0]-Xcords [1]-Ycords
	std::vector<Food*> currentEffects {};

	int snakeLength = 6;
	bool isAlive = true;
	int score = 0;

	float snakeMaxMoveTime = 0.30f;
	float snakeMoveTimer = 0.0f;

	char currentDirection; //MA£E LITERY!!!! 'w'-góra 's'-dó³ 'a'-lewo 'd'-prawo
	const int inputQueueMaxSize = 2;
	std::queue<char> inputQueue;

public:
	Snake(int x, int y, char direction);

	void snakeDirectionChange(const sf::Event::KeyPressed& key);

	void snakeMove(float deltaTime, std::vector<std::vector<char>>& board);

	bool isValidMove(int &x, int &y, std::vector<std::vector<char>>& board);

	void snakeDeath();

	bool getStatus();

	void snakeEat(Food& food);

	void snakeVomit();

	void addScore(int amount);

	int getScore();

	char getDirection();

	const std::vector<std::array<int, 2>>& getSnakeCords() const;

	float getMaxMoveTime();

	void setMaxMoveTime(float maxTime);
};

