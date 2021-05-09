//
//  Header.h
//  Hangman_20020282
//
//  Created by John Vu on 08/05/2021.
//

#ifndef Header_h
#define Header_h

#include <SDL2/SDL_mixer.h>
#include <SkickSDL.hpp>

const int SCREEN_WIDTH = 950;                   // SDL window width
const int SCREEN_HEIGHT = 900;                  // SDL window height
const std::string WINDOW_TITLE = "Hangman";     // SDL window title

extern Mix_Music* BackgroundMusic;              // Background Music
extern Mix_Chunk* startSFX;                     // start SFX
extern Mix_Chunk* correctSFX;                   // correct SFX
extern Mix_Chunk* incorrectSFX;                 // incorrect SFX
extern Mix_Chunk* deadSFX;                      // dead SFX
extern Mix_Chunk* aliveSFX;                     // alive SFX

#endif /* Header_h */
