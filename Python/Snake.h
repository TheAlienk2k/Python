#pragma once
#include <SFML/Graphics.hpp>
#include "LevelMenager.h"

#include <vector>
#include <array>
#include <queue>
#include <algorithm>

class Snake
{
private:
	vector<vector<char>> board;
	vector<array<int, 2>> snakeBlocksCords; //[0]-Xcords [1]-Ycords
	int snakeLength = 6;
	char snakeDirection; //MA£E LITERY!!!! 'w'-góra 's'-dó³ 'a'-lewo 'd'-prawo
	bool isAlive = true;

	float snakeMaxMoveTime = 0.15f;
	float snakeMoveTimer = 0.0f;

	const int inputQueueMaxSize = 2;

	char currentDirection;
	queue<char> inputQueue;
public:
	Snake(int x, int y, char direction, vector<vector<char>>& board)
	:board(board)
	{
		snakeBlocksCords.insert(snakeBlocksCords.begin(), std::array{x , y});
		currentDirection = direction;
	}

	void snakeDirectionChange(const sf::Event::KeyPressed& key) {
		if (isAlive == false) return;

		if ((key.code == sf::Keyboard::Key::W)) {
			if (!inputQueue.empty()) {
				if ((inputQueue.size() <= inputQueueMaxSize) && (inputQueue.back() != 's')) {
					inputQueue.push('w');
				}
			}
			else if (currentDirection != 's') {
					inputQueue.push('w');
			}
		}
		else if ((key.code == sf::Keyboard::Key::S)) {
			if (!inputQueue.empty()) {
				if ((inputQueue.size() <= inputQueueMaxSize) && (inputQueue.back() != 'w')) {
					inputQueue.push('s');
				}
			}
			else if (currentDirection != 'w') {
					inputQueue.push('s');
			}
		}
		else if(key.code == sf::Keyboard::Key::A) {
			if (!inputQueue.empty()) {
				if ((inputQueue.size() <= inputQueueMaxSize) && (inputQueue.back() != 'd')) {
					inputQueue.push('a');
				}
			}
			else if (currentDirection != 'd') {
				inputQueue.push('a');
			}
		}
		else if(key.code == sf::Keyboard::Key::D) {
			if (!inputQueue.empty()) {
				if ((inputQueue.size() <= inputQueueMaxSize) && (inputQueue.back() != 'a')) {
					inputQueue.push('d');
				}
			}
			else if (currentDirection != 'a') {
				inputQueue.push('d');
			}
		}

	}

	void snakeMove(float deltaTime){
		snakeMoveTimer += deltaTime;

		if (snakeMoveTimer >= snakeMaxMoveTime && isAlive) {
			
				int snakeHeadX = snakeBlocksCords.at(0)[0];
				int snakeHeadY = snakeBlocksCords.at(0)[1];
				cout << "kierunek w snaku " << snakeDirection << "\n";

				if (currentDirection == 'w') {
					if ((board[snakeHeadY - 1][snakeHeadX] != '#') &&
						(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX , snakeHeadY - 1 }) == snakeBlocksCords.end()))
					{
						snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX,snakeHeadY - 1 });
						if (snakeBlocksCords.size() > snakeLength) {
							snakeBlocksCords.pop_back();
						}
					}
					else {
						this->snakeDeath();
					}
				}
				else if (currentDirection == 's') {
					if ((board[snakeHeadY + 1][snakeHeadX] != '#') &&
						(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX , snakeHeadY + 1 }) == snakeBlocksCords.end()))
					{
						snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX,snakeHeadY + 1 });
						if (snakeBlocksCords.size() > snakeLength) {
							snakeBlocksCords.pop_back();
						}
					}
					else {
						this->snakeDeath();
					}
				}
				else if (currentDirection == 'a') {
					if ((board[snakeHeadY][snakeHeadX - 1] != '#') &&
						(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX - 1, snakeHeadY }) == snakeBlocksCords.end()))
					{
						snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX - 1,snakeHeadY });
						if (snakeBlocksCords.size() > snakeLength) {
							snakeBlocksCords.pop_back();
						}
					}
					else {
						this->snakeDeath();
					}
				}
				else if (currentDirection == 'd') {
					if ((board[snakeHeadY][snakeHeadX + 1] != '#') &&
						(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX + 1, snakeHeadY }) == snakeBlocksCords.end()))
					{
						snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX + 1,snakeHeadY });
						if (snakeBlocksCords.size() > snakeLength) {
							snakeBlocksCords.pop_back();
						}
					}
					else {
						this->snakeDeath();
					}
				}

				if (inputQueue.size() > 0) {
					currentDirection = inputQueue.front();
					inputQueue.pop();
				}

			snakeMoveTimer = 0.0f;
		}
	}

	void snakeDeath() {
		isAlive = false;
		queue<char> emptyQueue;
		swap(inputQueue, emptyQueue);
	}

	void snakeEat() {
		snakeLength++;
	}

	void snakeVomit() {
		snakeLength--;
	}

	bool getStatus() {
		return isAlive;
	}

	char getDirection() {
		return currentDirection;
	}

	vector<array<int, 2>> getSnakeCords() {
		return snakeBlocksCords;
	}
};

