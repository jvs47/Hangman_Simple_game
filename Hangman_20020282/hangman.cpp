//
//  hangman.cpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

#include "coreGame.hpp"
#include "SkickSDL.hpp"

using namespace std;

const int SCREEN_WIDTH = 1440;           // SDL window width
const int SCREEN_HEIGHT = 900;          // SDL window height
const string WINDOW_TITLE = "Hangman";  // SDL window title

int main(int argc, char* argv[]) {
    // initialize SkickSDL window
    SkickSDL* SDL = new SkickSDL(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL->openFont("/Users/jvs47/Downloads/Hangman-master/VeraMoBd.ttf", 30); // text font and size
    srand( static_cast<unsigned int>(time(nullptr))); // random seeds
    coreGame* hangman = new coreGame(SDL);  // initialize game
    while (hangman->playing) {                 // while player is playing game
        hangman->welcome();
        hangman->startGame();                  // start a game
        do {                                   // initialize game loop for rendering
            hangman->renderGameSDL();          // render SDL game1
            hangman->guessEvent();             // handle SDL keypress event
            hangman->handleGuess();            // handle game based on event
            hangman->updateTime();             // update playTime
        } while (hangman->guessing());         // render game if the player is guessing
        hangman->gameOver();                   // handle game over data and render SDL
    }
    return 0;
}

