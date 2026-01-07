#include "Menagers/LevelMenager.h"

LevelMenager::LevelMenager(const std::string fName) : folderName(fName), currentLevel(0) {
	updateCurrentLevelNamesList();
}

std::string LevelMenager::getCurrentLevelName() {
	if (levelsDataVector.empty()) {
		return "";
	}

	return levelsDataVector[currentLevel].name;
}

void LevelMenager::updateCurrentLevelNamesList() {
	std::vector<FileData> newFiles;

	for (const auto& file : std::filesystem::directory_iterator(folderName)) {
		if (file.is_regular_file() && file.path().extension() == ".txt") {
			std::string fileName = file.path().stem().string();
			auto fileTime = std::filesystem::last_write_time(file);

			bool alreadyExists = false;
			for (const auto& level : levelsDataVector) {
				if (level.name == fileName) {
					alreadyExists = true;
					break;
				}
			}

			if (!alreadyExists) {
				newFiles.push_back({ fileName, fileTime });
			}
		}
	}

	if (!newFiles.empty()) {
		std::sort(newFiles.begin(), newFiles.end(), [](const FileData& a, const FileData& b) {
			if (a.time != b.time) return a.time < b.time;
			return a.name < b.name;
			});

		for (const auto& file : newFiles) {
			levelsDataVector.push_back(file);
		}

		currentLevelBoard = updateBoard();
	}
}

bool LevelMenager::isLevelValid(std::filesystem::path levelPath) {
	std::ifstream file(levelPath);
	if (!file.is_open()) { throw std::runtime_error("Nie udalo sie otworzyc \npliku poziomu"); }

	bool hasS = false;
	bool hasD = false;

	std::string prev;
	std::string curr;
	std::string next;

	int longestRowSize = 0;
	bool endOfFile = false;

	if (!std::getline(file, curr)) { throw std::runtime_error("Plik poziomu jest pusty."); }
	longestRowSize = curr.size();

	while (!endOfFile) {
		if (!std::getline(file, next)) {
			next = "";
			endOfFile = true;
		}
		else {
			if (next.size() > longestRowSize) longestRowSize = next.size();
		}

		for (int x = 0; x < curr.size(); ++x) {
			char currC = curr[x];

			if (!strchr(" #dDsS", currC)) { throw std::runtime_error("Poziom zawiera niedozwolony \nznak: " + std::string(1, currC)); }

			char c = std::tolower(static_cast<unsigned char>(currC));

			if (c == 's' || c == 'S') hasS = true;
			if (c == 'd' || c == 'D') hasD = true;

			if (c == 's') {
				bool foundD = false;

				if (x > 0 && std::tolower(static_cast<unsigned char>(curr[x - 1])) == 'd') foundD = true;
				if (!foundD && x < curr.size() - 1 && std::tolower(static_cast<unsigned char>(curr[x + 1])) == 'd') foundD = true;

				if (!foundD && !prev.empty() && x < prev.size()) {
					if (std::tolower(static_cast<unsigned char>(prev[x])) == 'd') foundD = true;
				}

				if (!foundD && !next.empty() && x < next.size()) {
					if (std::tolower(static_cast<unsigned char>(next[x])) == 'd') foundD = true;
				}

				if (!foundD) { throw std::runtime_error("Waz (S) musi sasiadowac z \nkierunkiem startowym (D)!"); }
			}
		}

		prev = curr;
		curr = next;
	}

	if (!hasS) { throw std::runtime_error("Poziom musi zawierac znak \nstartu S!"); }
	if (!hasD) { throw std::runtime_error("Poziom musi zawierac znak \nkierunku D!"); }

	if (longestRowSize < minBoardSize || longestRowSize > maxBoardSize) { throw std::runtime_error("Mapa musi miec szerokosc i \ndlugosc w przedziale od 5 do 40"); }

	return true;
}

void LevelMenager::fixFileLinesLength(std::filesystem::path levelPath) {
	std::vector<std::string> lines;
	std::string line;
	size_t maxLength = 0;


	std::ifstream inFile(levelPath);
	while (std::getline(inFile, line)) {
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		lines.push_back(line);
		if (line.length() > maxLength) {
			maxLength = line.length();
		}
	}
	inFile.close();

	std::ofstream outFile(levelPath, std::ios::trunc);
	for (size_t i = 0; i < lines.size(); ++i) {
		std::string currentLine = lines[i];

		if (currentLine.length() < maxLength) {
			currentLine.append(maxLength - currentLine.length(), ' ');
		}

		outFile << currentLine;

		if (i < lines.size() - 1) {
			outFile << "\n";
		}
	}
	outFile.close();
}

bool LevelMenager::isLevelListEmpty() {
	if (levelsDataVector.empty()) {
		return true;
	}
	else {
		return false;
	}
}

void LevelMenager::nextLevel() {
	if (levelsDataVector.empty()) { return; }

	if (currentLevel == levelsDataVector.size() - 1) {
		currentLevel = 0;
	}
	else {
		currentLevel++;
	}

	currentLevelBoard = this->updateBoard();
}

void LevelMenager::previousLevel() {
	if (levelsDataVector.empty()) { return; }

	if (currentLevel == 0) {
		currentLevel = levelsDataVector.size() - 1;
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
				else if ((x < currentLevelBoard[y].size() - 1) && (currentLevelBoard[y][x + 1] == 'D' || currentLevelBoard[y][x + 1] == 'd')) {
					return 'd';
				}
				else if ((y < currentLevelBoard.size() - 1) && (currentLevelBoard[y + 1][x] == 'D' || currentLevelBoard[y + 1][x] == 'd')) {
					return 's';
				}
				else if ((x > 0) && (currentLevelBoard[y][x - 1] == 'D' || currentLevelBoard[y][x - 1] == 'd')) {
					return 'a';
				}
			}
		}
	}
	return 'd';
}

std::array<int, 2> LevelMenager::getSnakeCordsAtStart() {
	for (int y = 0; y < currentLevelBoard.size(); y++) {
		for (int x = 0; x < currentLevelBoard[y].size(); x++) {
			if (currentLevelBoard[y][x] == 'S' || currentLevelBoard[y][x] == 's') {
				return std::array<int, 2>{x, y};
			}
		}
	}

	return std::array<int, 2>{0, 0};
}

std::vector<std::vector<char>> LevelMenager::updateBoard() {
	std::vector<std::vector<char>> board;
	std::string fName = levelsDataVector[currentLevel].name;

	std::ifstream file(folderName + "\\" + fName + ".txt");
	if (file.is_open()) {
		std::cout << "otwarto: " << folderName + "\\" + fName + ".txt" << "\n";
	}
	else {
		std::cout << "Blad przy otwarciu pliku: " << fName << ".txt" << "\n";
	}

	std::string currentLine = "";
	while (getline(file, currentLine)) {
		std::vector<char> row;
		for (char c : currentLine) {
			row.push_back(c);
		}
		board.push_back(row);
	}

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			std::cout << board[i][j];
		}
		std::cout << "\n";
	}

	file.close();
	return board;
}

std::vector<std::vector<char>> LevelMenager::getLevelBoard() {
	return currentLevelBoard;
}

void LevelMenager::removeCurrentLevel() {
	if (levelsDataVector.empty()) { return; }

	try {
		if (std::filesystem::remove(std::filesystem::path(folderName) / (levelsDataVector.at(currentLevel).name + ".txt"))) {
			std::string scoresPath = "SavedData\\BestScores.json";
			json scoresData;
			std::ifstream inFile(scoresPath);
			inFile >> scoresData;

			scoresData.erase(levelsDataVector.at(currentLevel).name + ".txt");
			std::ofstream outFile(scoresPath);
			outFile << scoresData.dump(3);

			levelsDataVector.erase(levelsDataVector.begin() + currentLevel);

			std::cout << "Level zostal usuniety!" << std::endl;

			if (levelsDataVector.empty()) {
				currentLevel = 0;
			}
			else if (currentLevel >= levelsDataVector.size()) {
				currentLevel = levelsDataVector.size() - 1;
			}

		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Blad podczas usuwania pliku: " << e.what() << std::endl;
	}
}

void LevelMenager::addNewLevel() {

#ifdef _WIN32
	std::filesystem::path filePath = windowsFileSelection();

	if (!filePath.empty()) {
		try {
			if (isLevelValid(filePath)) {
				std::filesystem::path destination = "Levels" / filePath.filename();
				std::filesystem::copy_file(filePath, destination, std::filesystem::copy_options::overwrite_existing);

				std::string scoresPath = "SavedData\\BestScores.json";
				json scoresData;

				if (std::filesystem::file_size(scoresPath) > 0) {
					std::ifstream inFile(scoresPath);
					inFile >> scoresData;
				}
				else {
					scoresData = json::object();
				}

				std::string levelName = filePath.filename().string();
				scoresData[levelName] = 0;

				std::ofstream outFile(scoresPath);
				outFile << scoresData.dump(3);

				std::cout << "Udalo sie skopiowac" << std::endl;

				fixFileLinesLength(destination);
				updateCurrentLevelNamesList();
			}
		}
		catch (const std::filesystem::filesystem_error& e) {
			throw std::runtime_error("Nieznany blad systemu plikow");
		}
	}
#else
	throw std::runtime_error("Dodawanie poziomow jest dostepne tylko na Windows");
#endif
}

void LevelMenager::saveScoreToJson(int score) {
	std::string scoresPath = "SavedData\\BestScores.json";
	json scoresData;
	std::ifstream inFile(scoresPath);
	inFile >> scoresData;

	if (score > scoresData[levelsDataVector.at(currentLevel).name + ".txt"]) {
		scoresData[levelsDataVector.at(currentLevel).name + ".txt"] = score;
	}
	std::ofstream outFile(scoresPath);
	outFile << scoresData.dump(3);
}

int LevelMenager::getBestScoreFromJson() {
	std::string scoresPath = "SavedData/BestScores.json";

	if (levelsDataVector.empty()) { return 0; }

	std::string levelKey = levelsDataVector.at(currentLevel).name + ".txt";
	std::ifstream inFile(scoresPath);
	if (!inFile.is_open()) { return 0; }

	nlohmann::json scoresData;
	inFile >> scoresData;
	if (scoresData.contains(levelKey)) {
		return scoresData[levelKey].get<int>();
	}

	return 0;
}

#ifdef _WIN32
std::filesystem::path LevelMenager::windowsFileSelection(HWND owner) {
	std::filesystem::path selectedPath = "";

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileOpenDialog* pFileOpen;
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr)) {
			COMDLG_FILTERSPEC rgSpec[] = {
				{ L"Text Files (*.txt)", L"*.txt" }
			};
			pFileOpen->SetFileTypes(1, rgSpec);
			pFileOpen->SetFileTypeIndex(1);
			hr = pFileOpen->Show(owner);

			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr)) {
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr)) {
						selectedPath = std::filesystem::path(pszFilePath);

						CoTaskMemFree(pszFilePath);
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return selectedPath;
}
#endif