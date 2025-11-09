#include <iostream> 
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "LevelMenager.h"
#include "MainMenuScene.h"
#include "SceneMenager.h"

using namespace std;

int main()
{
    sf::RenderWindow gameWindow(sf::VideoMode({ 1366, 768 }), "Python The Game", sf::Style::Titlebar | sf::Style::Close);
    LevelMenager levelMenager("Levels");

    const float maxFps = 60.0f;
    const sf::Time frameTime = sf::seconds(1.0f / maxFps);

    sf::Clock gameClock;
    sf::Time frameAccumulator = sf::Time::Zero;

    SceneMenager sceneMenager(gameWindow, levelMenager);
    sceneMenager.loadMainMenu();

    bool stateChanged = true;


    while (gameWindow.isOpen())
    {
        
        while (const optional event = gameWindow.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                gameWindow.close();
            }

            if (event.has_value()) {
                sceneMenager.currentScene->eventHandler(event.value(), gameWindow);
                stateChanged == true;
            }
        }

        sf::Time deltaTime = gameClock.restart();
        frameAccumulator += deltaTime;
        while (frameAccumulator >= frameTime) {
            sceneMenager.currentScene->update(frameTime.asSeconds());
            stateChanged == true;
            frameAccumulator -= frameTime;
        }

        if (stateChanged == true) {                        //Trzeba bedzie to zmeiniæ gdy w przysz³oœci zostan¹ dodane jakieœ animacje np do textury snake
            gameWindow.clear(sf::Color::Black);
            sceneMenager.currentScene->render(gameWindow);
            gameWindow.display();

            stateChanged == false;
        }

    }
    
}