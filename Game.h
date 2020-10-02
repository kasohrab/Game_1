//
// Created by Alex Sohrab on 10/1/20.
//
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#ifndef GAME_1_GAME_H
#define GAME_1_GAME_H
#pragma once

/*
 * Class that acts as game engine Wrapper class.
 */

class Game {
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;
    void initVariables();
    void initWindow();
public:
    //Constructors / Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running();

    //Functions
    void update();
    void render();
    void pollEvents();


};


#endif //GAME_1_GAME_H
