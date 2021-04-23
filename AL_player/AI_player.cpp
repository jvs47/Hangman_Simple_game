//
//  AI_player.cpp
//  Hangman_20020282
//
//  Created by John Vu on 23/04/2021.
//
#include <iostream>
#include <set>
#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "guesser.hpp"

using namespace std;

const int SCREEN_WIDTH = 1440;           // SDL window width
const int SCREEN_HEIGHT = 900;          // SDL window height
const string WINDOW_TITLE = "AI_Player";  // SDL window title

int main(int argc, char* argv[])
{
    SkickSDL* SDL = new SkickSDL(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL->openFont("/Users/jvs47/Downloads/Hangman-master/VeraMoBd.ttf", 30); // text font and size
    Guesser* guesser = new Guesser(SDL);
    while(guesser->playing)
    {
        guesser->newGame();
        
    /*render(guesser);
    do {
        char guess = guesser->getNextGuess();
        if (guess == 0) {
            cout << "I give up, hang me" << endl;
            return 0;
        }

        do {
            try {
                string mask = getUserAnswer(guess);
                guesser->receiveHostAnswer(guess, mask);
                break;
            } catch (invalid_argument e) {
                cout << "Invalid mask, try again" << endl;
            }
        } while (true);
        render(guesser);
    
    playAnimation(guesser);

    }*/
        do{
            guesser->renderGameSDL();
            
        }
        guesser->gameOver();
    }
    return 0;
}
