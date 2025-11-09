#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

class LevelMenager {
private:
    vector<string> levelNames;
    const string folderName;
    int currentLevel = 0;

public:
    LevelMenager(const string fName = "Levels");
    string getCurrentLevelName();
    void nextLevel();
    void previousLevel();
    vector<vector<char>> getCurrentBoard();
};