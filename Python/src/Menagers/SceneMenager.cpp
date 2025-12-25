#include "Menagers/SceneMenager.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/LevelSelectScene.h"
#include "Scenes/GameScene.h"

SceneMenager::SceneMenager(sf::RenderWindow& window, LevelMenager& levelMenager)
    :gameWindow(window)
    ,levelMenager(levelMenager) {
}

void SceneMenager::loadMainMenu() {
    currentScene = std::make_unique<MainMenuScene>(gameWindow, this);
}

void SceneMenager::loadLevelSelectScene() {
    currentScene = std::make_unique<LevelSelectScene>(gameWindow, this, levelMenager);
}

void SceneMenager::loadGameScene() {
    currentScene = std::make_unique<GameScene>(gameWindow, this, levelMenager);
}
