#include <iostream> 
#include <SFML/Graphics.hpp>

#include "Scene.h"
#include "MainMenuScene.h"
#include "SceneMenager.h"
using namespace std;

int main()
{
    sf::RenderWindow gameWindow(sf::VideoMode({ 1366, 768 }), "Python The Game", sf::Style::Titlebar | sf::Style::Close);

    SceneMenager menager(gameWindow);
    menager.loadMainMenu();

    while (gameWindow.isOpen())
    {
        
        while (const optional event = gameWindow.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                gameWindow.close();
            }

            if (event.has_value()) {
                menager.currentScene->eventHandler(event.value(), gameWindow);
            }
        }

        gameWindow.clear(sf::Color::Black);
        menager.currentScene->render(gameWindow);
        gameWindow.display();

    }
    
}