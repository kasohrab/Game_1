//
// Created by Alex Sohrab on 10/1/20.
//

#include "Game.h"

//private
void Game::initVariables() {
    this->window = nullptr;

    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;


}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode,"Game 1",
                                        sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}


void Game::initEnemies() {
    this->enemy.setPosition(10.f,10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    //scales down size by factor of .5
    this->enemy.setScale(sf::Vector2f(.5f, .5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);


}

void Game::updateMousePositions() {
     /**
      * @return void
      * Updates position relative to window (Vector2i)
     */

     this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Game::spawnEnemy() {
    /**
     * @return void
     * Spawns and sets enemy color and position
     * Sets random position and color
     * Adds enemy to vector
    */

    //Sets at random x position at the top of the window
    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>((this->window->getSize().x) - this->enemy.getSize().x)),
            0.f);
    this->enemy.setFillColor(sf::Color::Green);

    //Spawn enemy
    this->enemies.push_back(this->enemy);
}

void Game::updateEnemies() {
    /**
     * @return void
     * Updates spawn timer and spawns enemies when the total amount is less than max enemies
     * Moves the enemies downwards
     * Removes enemies at the edge of the screen. //TDO
    */
    //Updating timer
    if (this->enemies.size() < this-> maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            //spawn and reset timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Move the enemies
    for (auto &e : this->enemies) {
        e.move(0.f, 5.f);
    }
}

void Game::renderEnemies() {
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}


//Constructors / Destructors
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initEnemies();
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

    this->updateMousePositions();

    this->updateEnemies();
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
    this->window->clear();

    //Draws game objects
    this->renderEnemies();

    this->window->display();

}









