//
//  mode.hpp
//  Hangman_20020282
//
//  Created by John Vu on 01/05/2021.
//

#ifndef mode_hpp
#define mode_hpp

#include <stdio.h>
#include "SkickSDL.hpp"
class gameMode
{
private:
    SkickSDL* SDL;
public:
    int mode;
    bool running;
    gameMode(SkickSDL*);
    void modeGame();
    void renderMode();
    void handleMode();
    
};
#endif /* mode_hpp */
