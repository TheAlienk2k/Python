#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Scene;
class MainMenuScene;
class LevelSelectScene;

class SceneMenager {
private:
    sf::RenderWindow& gameWindow;

public:
    std::unique_ptr<Scene> currentScene;

    SceneMenager(sf::RenderWindow& window);

    void loadMainMenu();
    void loadLevelSelectScene();
};

