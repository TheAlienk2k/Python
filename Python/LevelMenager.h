#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include <array>

using namespace std;

class LevelMenager {
private:
    vector<vector<char>> currentLevelBoard;
    vector<string> levelNames;
    const string folderName;
    int currentLevel = 0;

    vector<vector<char>> updateBoard();

public:
    LevelMenager(const string fName = "Levels");
    string getCurrentLevelName();
    void nextLevel();
    void previousLevel();
    char getSnakeDirectionAtStart();
    array<int, 2> getSnakeCordsAtStart();
    vector<vector<char>> getLevelBoard();
};