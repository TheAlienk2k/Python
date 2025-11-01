#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

class LevelMenager
{
private:
	vector<string> levelNames;
	const string folderName;

public:
	LevelMenager(const string fName = "Levels")
	: folderName(fName){
		
		for (const auto file : filesystem::directory_iterator(folderName)) {
			if (file.path().extension() == ".txt") {




				string fullFilePath = file.path().string();
				string fileName = fullFilePath.substr(fullFilePath.find_last_of("\\") + 1);
				levelNames.push_back(fileName.substr(0, fileName.find_last_of(".")));
			}
		}

	}

	vector<vector<char>> getBoardByName(string fName) {
		vector<vector<char>> board;

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

		for(int i = 0; i < board.size(); i++) {
			for(int j = 0; j < board[i].size(); j++) {
				cout << board[i][j] << " ";
			}
			cout << "\n";
		}

		file.close();

		return board;
	}

	vector<string>& getLevelNames() {
		return levelNames;
	}
};

