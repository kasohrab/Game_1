//
// Created by Alex Sohrab on 10/1/20.
//
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <sstream>
#include <filesystem>

#ifndef GAME_1_GAME_H
#define GAME_1_GAME_H
#pragma once

/**
 * Class that acts as game engine Wrapper class.
 */

class Game {
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;
    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    //Resources
    sf::Font font;
    //Text
    sf::Text uiText;
    //Game Logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Private functions
    void spawnEnemy();
    void updateEnemies();
    void renderEnemies(sf::RenderTarget& target);
    void initVariables();
    void initWindow();
    void initFonts();
    void initTexts();
    void initEnemies();

public:
    //Constructors / Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running();
    const bool getEndGame();

    //Functions
    void update();
    void render();
    void pollEvents();
    void updateMousePositions();
    void renderText(sf::RenderTarget& target);
    void updateText();


};


#endif //GAME_1_GAME_H
