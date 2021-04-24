//
//  SkickSDL.hpp
//  Hangman_20020282
//
//  Created by John Vu on 11/04/2021.
//

#ifndef SkickSDL_hpp
#define SkickSDL_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "painter.hpp"

using namespace std;

class SkickSDL
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Painter* painter;
    string title;
    int width;
    int height;
    
public:
    SkickSDL(string title_, int width_, int height_);
    ~SkickSDL();
    void logSDLError(ostream& os, const string& msg, bool fatal);
    void openFont(string f, int size);
    void createTextTexture(string text, int x, int y);
    void createImageBackground(string fileName);
    void createImage(string fileName, int x, int y);
    void updateScreen();
};
#endif /* SkickSDL_hpp */
