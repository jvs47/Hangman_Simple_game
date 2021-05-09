//
//  mode.hpp
//  Hangman_20020282
//
//  Created by John Vu on 01/05/2021.
//

#ifndef mode_hpp
#define mode_hpp

#include <stdio.h>
#include "WindowHeader.h"
#include "SkickSDL.hpp"

class gameMode
{
private:
    SkickSDL* SDL;
    int previous_Music;
    int previous_volume;

public:
    int mode;
    bool running;
    gameMode(SkickSDL*);
    void modeGame();
    void renderMode();
    void handleMode();
    
    void options();
    void renderOptions();
    void handleOptions();
    
};
#endif /* mode_hpp */
