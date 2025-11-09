#include "LevelMenager.h"

LevelMenager::LevelMenager(const string fName) : folderName(fName), currentLevel(0) {
    for (const auto& file : filesystem::directory_iterator(folderName)) {

        if (file.path().extension() == ".txt") {
            string fullFilePath = file.path().string();
            string fileName = fullFilePath.substr(fullFilePath.find_last_of("\\") + 1);

            levelNames.push_back(fileName.substr(0, fileName.find_last_of(".")));
        }

    }

    currentLevelBoard = updateBoard();
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

    currentLevelBoard = this->updateBoard();
}

void LevelMenager::previousLevel() {
    if (currentLevel == 0) {
        currentLevel = levelNames.size() - 1;
    }
    else {
        currentLevel--;
    }

    currentLevelBoard = this->updateBoard();
}

char LevelMenager::getSnakeDirectionAtStart() {
    for (int y = 0; y < currentLevelBoard.size(); y++) {
        for (int x = 0; x < currentLevelBoard[y].size(); x++) {
            if (currentLevelBoard[y][x] == 'S' || currentLevelBoard[y][x] == 's') {
                if ((y > 0) && (currentLevelBoard[y - 1][x] == 'D' || currentLevelBoard[y - 1][x] == 'd')) {
                    return 'w';
                }
                else if ((x < currentLevelBoard[y].size()-1) && (currentLevelBoard[y][x + 1] == 'D' || currentLevelBoard[y][x + 1] == 'd')) {
                    return 'd';
                }
                else if ((y < currentLevelBoard.size()-1) && (currentLevelBoard[y + 1][x] == 'D' || currentLevelBoard[y + 1][x] == 'd')) {
                    return 's';
                }
                else if ((x > 0) && (currentLevelBoard[y][x - 1] == 'D' || currentLevelBoard[y][x - 1] == 'd')) {
                    return 'a';
                }
            }
        }
    }

    cout << "To nic" << "\n";
    return 'd';
}

array<int, 2> LevelMenager::getSnakeCordsAtStart() {
    for (int y = 0; y < currentLevelBoard.size(); y++) {
        for (int x = 0; x < currentLevelBoard[y].size(); x++) {
            if (currentLevelBoard[y][x] == 'S' || currentLevelBoard[y][x] == 's') {
                return array<int, 2>{x, y};
            }
        }
    }

    return array<int, 2>{0, 0};
}

vector<vector<char>> LevelMenager::updateBoard() {
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

vector<vector<char>> LevelMenager::getLevelBoard() {
    return currentLevelBoard;
}