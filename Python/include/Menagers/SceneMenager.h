#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Scene;
class MainMenuScene;
class LevelSelectScene;
class LevelMenager;

class SceneMenager {
private:
    sf::RenderWindow& gameWindow;
    LevelMenager& levelMenager;

public:
    std::unique_ptr<Scene> currentScene;

    SceneMenager(sf::RenderWindow& window, LevelMenager& levelMenager);

    void loadMainMenu();
    void loadLevelSelectScene();
    void loadGameScene();
};

