//
// Created by Alex Sohrab on 10/1/20.
//

#include "Game.h"

//private
void Game::initVariables() {
    this->window = nullptr;

    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->health = 10;
    this->endGame = false;

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
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);


}

void Game::initFonts() {
    std::stringstream fontPathName;
    fontPathName << std::__fs::filesystem::current_path() ;
    std::string pathName = fontPathName.str().substr(1);
    pathName = pathName.substr(0,pathName.size()-1);
    pathName += "/Fonts/Dosis-Light.ttf";
    if (!this->font.loadFromFile(pathName)) {
        std::cout << pathName;
        std::cout <<"ERROR::GAME::INITFONTS: Failed to load.";
    };

}

void Game::initTexts() {
    this->uiText.setFont(this->font);
    this->uiText.setPosition(0.f,0.f);
    this->uiText.setCharacterSize(32);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::updateMousePositions() {
     /**
      * @return void
      * Updates position relative to window (Vector2i)
     */

     this->mousePosWindow = sf::Mouse::getPosition(*this->window);
     this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
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
     * Removes enemies at the edge of the screen.
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

    //Move and updating the enemies
    for (int i = 0; i < this->enemies.size(); i++) {

        this->enemies[i].move(0.f, 4.f);
        //If enemy is below screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            //Lose health
            this->health -= 1;
        }
    }

    //Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;
            bool deleted = false;
            //if in range of enemy
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Delete enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                    //Gain points
                    this->points += 1;
                }
            }
        }
    }
    //Makes it required to click on each enemy
    else {
        this->mouseHeld = false;
    }

}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

//Constructors / Destructors
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initTexts();
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

    if (this->endGame == false) {
        this->updateMousePositions();

        this->updateEnemies();

        this->updateText();
    }

    //End game condition
    if (this-> health <= 0)
        this->endGame = true;
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
    this->renderText(*this->window);

    this->renderEnemies(*this->window);

    this->window->display();
}



void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << "\n"
    << "Health: " << this->health;
    this->uiText.setString(ss.str());
}

const bool Game::getEndGame() {
    return this->endGame;
}















