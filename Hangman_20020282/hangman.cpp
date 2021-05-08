//
//  hangman.cpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

#include "WindowHeader.h"
#include "mode.hpp"
#include "coreGame.hpp"
#include "guesser.hpp"
#include "SkickSDL.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    SkickSDL* SDL = new SkickSDL(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT); // initialize SkickSDL window
    SDL->openFont("/Users/jvs47/Downloads/Hangman-master/VeraMoBd.ttf", 30); // text font and size
    srand( static_cast<unsigned int>(time(nullptr)));                        // random seeds
    gameMode* mode = new gameMode(SDL);
    
    while(mode->running)
    {
        mode->modeGame();
        if(mode->mode == 1)
        {
            coreGame* hangman = new coreGame(SDL);     // initialize game
            while (hangman->playing) {                 // while player is playing game
                hangman->startGame();                  // start a game
                do {                                   // initialize game loop for rendering
                    hangman->renderGameSDL();          // render SDL game1
                    hangman->guessEvent();             // handle SDL keypress event
                    hangman->handleGuess();            // handle game based on event
                    hangman->updateTime();             // update playTime
                } while (hangman->guessing());         // render game if the player is guessing
                hangman->gameOver();                   // handle game over data and render SDL
            }
        }
        else if(mode->mode == 0)
        {
            Guesser* guesser = new Guesser(SDL);       // initialize ai
            while(guesser->playing)                    //while com is playing
            {
                guesser->newGame();                    //start new game
                char guess;
                do {
                    guess = guesser->getNextGuess();   //handle come guess
                    guesser->renderGameSDL(guess);     //render SDL game
                    if (guess == 0) {
                        break;
                    }
                    do {
                        try {
                            string mask = guesser->getUserAnswer(guess);    //input mask
                            guesser->receiveHostAnswer(guess, mask);        //handle mask
                            break;
                        } catch (invalid_argument e) {                      //handle exception
                            cout << "Invalid mask, try again" << endl;
                        }
                    } while (true);
                    //guesser->renderGameSDL(guess);
                } while (!guesser->isStop());   //render game if com still guessing
                if(guess == 0)
                    guesser->giveUp();          //com give up
                else
                    guesser->gameOver();        //gameOver
            }
        }
        else
            break;
    }
    return 0;
}
