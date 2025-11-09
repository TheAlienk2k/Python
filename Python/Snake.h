#pragma once
#include <SFML/Graphics.hpp>
#include "LevelMenager.h"

#include <vector>
#include <array>
#include <algorithm>

class Snake
{
private:
	vector<vector<char>> board;
	vector<array<int, 2>> snakeBlocksCords; //[0]-Xcords [1]-Ycords
	int snakeLength = 1;
	char snakeDirection = 'd'; //MA£E LITERY!!!! 'w'-góra 's'-dó³ 'a'-lewo 'd'-prawo
	bool isAlive = true;

public:
	Snake(int x, int y, char direction, vector<vector<char>> board)
	:board(board)
	{
		snakeBlocksCords.insert(snakeBlocksCords.begin(), std::array{x , y});
		snakeDirection = direction;
	}

	void snakeDirectionChange(const sf::Event::KeyPressed& key) {
		if(key.code == sf::Keyboard::Key::W) {
			snakeDirection = 'w';
		}
		else if(key.code == sf::Keyboard::Key::S) {
			snakeDirection = 's';
		}
		else if(key.code == sf::Keyboard::Key::A) {
			snakeDirection = 'a';
		}
		else if(key.code == sf::Keyboard::Key::D) {
			snakeDirection = 'd';
		}

		std::cout << "Zmieniono kierunek na: " << snakeDirection << "\n";
	}

	void snakeMove(){
		int snakeHeadX = snakeBlocksCords.at(0)[0];
		int snakeHeadY = snakeBlocksCords.at(0)[1];

		if (snakeDirection = 'w') {
			if ((board[snakeHeadY - 1][snakeHeadX] == ' ') &&
				(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX , snakeHeadY - 1 }) != snakeBlocksCords.end())) 
			{
				snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX,snakeHeadY - 1});
				snakeBlocksCords.pop_back();
			}
			else {
				isAlive = false;
			}
		}
		else if (snakeDirection = 's') {
			if ((board[snakeHeadY + 1][snakeHeadX] == ' ') &&
				(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX , snakeHeadY + 1}) != snakeBlocksCords.end()))
			{
				snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX,snakeHeadY + 1});
				snakeBlocksCords.pop_back();
			}
			else {
				isAlive = false;
			}
		}
		else if (snakeDirection = 'a') {
			if ((board[snakeHeadY][snakeHeadX - 1] == ' ') &&
				(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX - 1, snakeHeadY}) != snakeBlocksCords.end()))
			{
				snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX-1,snakeHeadY});
				snakeBlocksCords.pop_back();
			}
			else {
				isAlive = false;
			}
		}
		else if (snakeDirection = 'd') {
			if ((board[snakeHeadY][snakeHeadX + 1] == ' ') &&
				(std::find(snakeBlocksCords.begin() + 1, snakeBlocksCords.end(), std::array{ snakeHeadX + 1, snakeHeadY}) != snakeBlocksCords.end()))
			{
				snakeBlocksCords.insert(snakeBlocksCords.begin(), { snakeHeadX+1,snakeHeadY});
				snakeBlocksCords.pop_back();
			}
			else {
				isAlive = false;
			}
		}
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

	vector<array<int, 2>> getSnakeCords() {
		return snakeBlocksCords;
	}
};

