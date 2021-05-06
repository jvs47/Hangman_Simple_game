//
//  mode.cpp
//  Hangman_20020282
//
//  Created by John Vu on 01/05/2021.
//

#include "mode.hpp"
#include "SkickSDL.hpp"

gameMode::gameMode(SkickSDL* SkickSDL): SDL(SkickSDL){
    running = true;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
       {
           cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
       }
    BackgroundMusic = Mix_LoadMUS("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/ambience_1.wav");
    if(BackgroundMusic==NULL)
        printf("Cant load bgMusic\n");
}

void gameMode::modeGame()
{
    mode = -1;
    if (!Mix_PlayingMusic())
        {
            Mix_PlayMusic(BackgroundMusic, -1);
        }
    while(mode == -1 && running)
    {
        renderMode();
        handleMode();
    }
}

void gameMode::renderMode()
{
    SDL->createImageBackground("intro.png");
    SDL->createTextTexture("WELCOME TO HANGMAN", 500, 150);
    SDL->createTextTexture("Select game Mode:", 550, 300);
    SDL->createTextTexture("1. Man player", 550, 350);
    SDL->createTextTexture("2. COM player", 550, 400);
    SDL->createTextTexture("Press ESC to Quit", 500, 675);
    SDL->updateScreen();
}

void gameMode::handleMode()
{
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running= false;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            running = false;
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '2')
                switch (keyName[0]) {
                    case '1':
                    {
                        running = true;
                        mode = 1;
                    }
                        break;
                    case '2':
                    {
                        running = true;
                        mode = 0;
                    }
                        break;
                }
        }
    }

}
