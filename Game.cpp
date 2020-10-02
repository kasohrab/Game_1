//
// Created by Alex Sohrab on 10/1/20.
//

#include "Game.h"
//private
void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Game 1",
                                        sf::Style::Titlebar | sf::Style::Close);
}

//Constructors / Destructors
Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

//Accessors
const bool Game::running() {
    return this->window->isOpen();
}

//Functions
void Game::update() {
    this->pollEvents();
}

void Game::pollEvents() {
    //Event polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::render() {
    /*
     *  @return void
     *  -clear old frame
     *  -render objects
     *  -display frame in window
     *
     * Renders the game objects
     */
    this->window->clear(sf::Color(255,0,0,255));

    //Draws game objects

    this->window->display();

}






