//
//  mode.cpp
//  Hangman_20020282
//
//  Created by John Vu on 01/05/2021.
//

#include "mode.hpp"
#include "WindowHeader.h"


Mix_Music* BackgroundMusic;
Mix_Chunk* startSFX;
Mix_Chunk* correctSFX;
Mix_Chunk* incorrectSFX;
Mix_Chunk* deadSFX;
Mix_Chunk* aliveSFX;

gameMode::gameMode(SkickSDL* SkickSDL): SDL(SkickSDL){
    running = true;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
       {
           cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
       }
    
    BackgroundMusic = Mix_LoadMUS("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/ambience_1.wav");
    startSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/gong.wav");
    correctSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/phew.wav");
    incorrectSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/rope-tighten.wav");
    deadSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/dead.wav");
    aliveSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/yeehaw.wav");
    
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
        options();
    }
}

void gameMode::renderMode()
{
    SDL->createImageBackground("intro.png");
    SDL->createTextTexture("WELCOME TO HANGMAN", 500, 150);
    SDL->createTextTexture("Select game Mode:", 550, 300);
    SDL->createTextTexture("1. Man player", 550, 350);
    SDL->createTextTexture("2. COM player", 550, 400);
    SDL->createTextTexture("3. Options", 550, 450);
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
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '3')
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
                    case '3':
                    {
                        running = true;
                        mode = 2;
                    }
                }
        }
    }

}

void gameMode::options()
{
    while(mode == 2 && running)
    {
        renderOptions();
        handleOptions();
    }
}

void gameMode::renderOptions()
{
    SDL->createImageBackground("intro.png");
    SDL->createTextTexture("__OPTIONS__", 500, 150);
    int temp1 = Mix_VolumeMusic(-1);
    string status1 = ((temp1!=0)? "ON":"OFF");
    SDL->createTextTexture("1. Music: " + status1, 500, 300);
    int temp2 = Mix_Volume(-1,-1);
    string status2 = ((temp2!=0)? "ON":"OFF");
    SDL->createTextTexture("2. SFX: " + status2, 500, 350);
    SDL->createTextTexture("3. Up", 500, 400);
    SDL->createTextTexture("4. Down", 500, 450);
    SDL->createTextTexture("Volume SFX: " + to_string(Mix_Volume(-1,-1)), 500, 500);
    SDL->createTextTexture("Press Enter to Return", 500, 600);
    SDL->updateScreen();
}

void gameMode::handleOptions()
{
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_RETURN ||event.key.keysym.sym == SDLK_RETURN2 ||event.key.keysym.sym == SDLK_KP_ENTER)) {
            running = true;
            mode = -1;
        } else if (event.type == SDL_KEYUP) {
            previous_Music = Mix_VolumeMusic(-1);
            previous_volume = Mix_Volume(-1,-1);
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '4')
                switch (keyName[0]) {
                    case '1':
                    {
                        if(previous_Music != 0)
                            Mix_VolumeMusic(0);
                        else Mix_VolumeMusic(128);
                    }
                        break;
                    case '2':
                    {
                        if(previous_volume != 0)
                            Mix_Volume(-1, 0);
                        else
                            Mix_Volume(-1, 128);
                    }
                        break;
                    case '3':
                    {
                        Mix_Volume(-1, previous_volume+1);
                    }
                        break;
                    case '4':
                    {
                        Mix_Volume(-1, previous_volume-1);
                    }
                        break;

                }
        }
    }
}
