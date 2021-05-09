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
#include "coreGame.hpp"
#include "guesser.hpp"

class gameMode
{
private:
    SkickSDL* SDL;
    int previous_Music;
    int previous_volume;

public:
    int mode;                       //mode number
    bool running;                   //running or not
    gameMode(SkickSDL*);            //initialize gameMode
    
    //choose mode game
    void modeGame();                
    void renderMode();
    void handleMode();
    
    // handle options
    void options();
    void renderOptions();
    void handleOptions();
    
    //clean game
    void clean();
};

void gameMode1(SkickSDL*);          //Player mode
void gameMode2(SkickSDL*);          //COM mode
#endif /* mode_hpp */
