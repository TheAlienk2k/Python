#pragma once

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    //File selectors - Only Windows
    #define byte win_byte
    #include <windows.h>
    #include <shobjidl.h>
    #undef byte
#else
   //Placeholder for non-Windows systems    
#endif

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <string>
#include <array>
#include <vector>

class LevelMenager {
private:
	const int minBoardSize = 5;
	const int maxBoardSize = 40;

    struct FileData {
        std::string name;
        std::filesystem::file_time_type time;
    };

    std::vector<std::vector<char>> currentLevelBoard;
    std::vector<FileData> levelsDataVector;
    const std::string folderName;
    int currentLevel = 0;

    std::vector<std::vector<char>> updateBoard();
    void updateCurrentLevelNamesList();
    bool isLevelValid(std::filesystem::path levelPath);
    void fixFileLinesLength(std::filesystem::path levelPath);

    #ifdef _WIN32
    std::filesystem::path windowsFileSelection(HWND owner = NULL);
    #endif

public:
    LevelMenager(const std::string fName = "Levels");
    std::string getCurrentLevelName();
    bool isLevelListEmpty();

    void nextLevel();
    void previousLevel();
    void removeCurrentLevel();
    void addNewLevel();

	void saveScoreToJson(int score);
	int getBestScoreFromJson();

    char getSnakeDirectionAtStart();
    std::array<int, 2> getSnakeCordsAtStart();
    std::vector<std::vector<char>> getLevelBoard();
};