#include "SceneMenager.h"
#include "MainMenuScene.h"
#include "LevelSelectScene.h"

SceneMenager::SceneMenager(sf::RenderWindow& window) : gameWindow(window) {}

void SceneMenager::loadMainMenu() {
    currentScene = std::make_unique<MainMenuScene>(gameWindow, this);
}

void SceneMenager::loadLevelSelectScene() {
    currentScene = std::make_unique<LevelSelectScene>(gameWindow, this);
}
