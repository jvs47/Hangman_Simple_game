//
//  hangman.cpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

#include "WindowHeader.h"
#include "mode.hpp"
#include "SkickSDL.hpp"

int main(int argc, char* argv[]) {
    
    SkickSDL* SDL = new SkickSDL(WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT); // initialize SkickSDL window
    SDL->openFont("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Font/FiraCode-SemiBold.ttf", 30); // text font and size

    srand( static_cast<unsigned int>(time(nullptr)));                        // random seeds
    gameMode* mode = new gameMode(SDL);
    
    while(mode->running)
    {
        mode->modeGame();                                                     // start game
    }
    mode->clean();                                                            // clean pointer
    
    return 0;
}
