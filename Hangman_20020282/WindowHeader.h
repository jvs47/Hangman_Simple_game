//
//  Header.h
//  Hangman_20020282
//
//  Created by John Vu on 08/05/2021.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <SDL2/SDL_mixer.h>

const int SCREEN_WIDTH = 950;           // SDL window width
const int SCREEN_HEIGHT = 900;          // SDL window height
const std::string WINDOW_TITLE = "Hangman";  // SDL window title

extern Mix_Music* BackgroundMusic;
extern Mix_Chunk* startSFX;
extern Mix_Chunk* correctSFX;
extern Mix_Chunk* incorrectSFX;
extern Mix_Chunk* deadSFX;
extern Mix_Chunk* aliveSFX;

#endif /* Header_h */
