#pragma once
#include <vector>
#include <filesystem>
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
				levelNames.push_back(fileName.substr(0, fileName.find_last_of(".") - 1));
			}
		}

	}

	vector<string>& getLevelNames() {
		return levelNames;
	}
};

