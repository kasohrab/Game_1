/**
 * Simple 2D Game made by following youtube tutorial at
 * https://www.youtube.com/watch?v=C06eGdy7C6k&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=3
 * @author kasohrab
 * @version 1.0
 */
#include "Game.h"

int main() {
    //init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //init Game engine
    Game game;

    //Game Loop
    while(game.running()) {

        //Update
        game.update();
        //Render
        game.render();
        //Draw your game

    }

    //End of application
    return 0;
}
