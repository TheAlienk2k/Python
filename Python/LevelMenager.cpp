#include "LevelMenager.h"

LevelMenager::LevelMenager(const string fName) : folderName(fName), currentLevel(0) {
    for (const auto& file : filesystem::directory_iterator(folderName)) {

        if (file.path().extension() == ".txt") {
            string fullFilePath = file.path().string();
            string fileName = fullFilePath.substr(fullFilePath.find_last_of("\\") + 1);

            levelNames.push_back(fileName.substr(0, fileName.find_last_of(".")));
        }

    }
}

string LevelMenager::getCurrentLevelName() {
    return levelNames[currentLevel];
}

void LevelMenager::nextLevel() {
    if (currentLevel == levelNames.size() - 1) {
        currentLevel = 0;
    }
    else {
        currentLevel++;
    }
}

void LevelMenager::previousLevel() {
    if (currentLevel == 0) {
        currentLevel = levelNames.size() - 1;
    }
    else {
        currentLevel--;
    }
}

vector<vector<char>> LevelMenager::getCurrentBoard() {
    vector<vector<char>> board;
    string fName = levelNames[currentLevel];
    cout << "otwarto: " << folderName + "\\" + fName + ".txt" << "\n";

    ifstream file(folderName + "\\" + fName + ".txt");
    if (!file.is_open()) {
        cout << "Blad przy otwarciu pliku: " << fName << ".txt" << endl;
    }

    string currentLine = "";
    while (getline(file, currentLine)) {
        vector<char> row;
        for (char c : currentLine) {
            row.push_back(c);
        }
        board.push_back(row);
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    file.close();
    return board;
}