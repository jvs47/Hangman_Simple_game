//
//  util.cpp
//  Hangman_20020282
//
//  Created by John Vu on 30/04/2021.
//

#include "util.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

string normalizeWord(const string s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

int generateRandomNumber(int min, int max)
{
    return rand() % (max-min) + min;
}

bool isCharInWord(char ch, string word)
{
    return (word.find_first_of(ch) != string::npos);
}

vector<string> readWordListFromFile(const string& filePath)
{
    vector<string> wordList;
    string word;
    ifstream wordFile(filePath);
    if (wordFile.is_open()) {
        while (wordFile >> word) {
            wordList.push_back(normalizeWord(word));
        }
        wordFile.close();
        return wordList;
    } else {
        throw domain_error("Error: Unable to open vocabulary file " + filePath);
    }
}

bool isAllDash(const string& s)
{
    for (char c : s)
        if (c != '-') return false;
    return true;
}

bool isAllNotDash(const string& s)
{
    for (char c : s)
        if (c == '-') return false;
    return true;
}

void clearScreen()
{
    system("clear");
}

std::string maskInput(SkickSDL* SDL)
{
    bool exit = false;

    //Event handler
    SDL_Event e;
    
    string inputText = "hello";

    //Set text color as black
    //SDL_Color textColor = { 0, 0, 0, 0xFF };
    
    //The current input text.
    SDL->createTextTexture(inputText.c_str(), 450, 450);

    //Enable text input
    SDL_StartTextInput();
    
    //While application is running
    while( !exit )
    {
        //The rerender text flag
        bool renderText = false;
        
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_RETURN ||e.key.keysym.sym == SDLK_RETURN2 ||e.key.keysym.sym == SDLK_KP_ENTER) )
            {
                exit = true;
            }
            //Special key input
            else if( e.type == SDL_KEYDOWN )
            {
                //Handle backspace
                if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
                {
                    //lop off character
                    inputText.pop_back();
                    renderText = true;
                }
                //Handle copy
                else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
                {
                    SDL_SetClipboardText( inputText.c_str() );
                }
                //Handle paste
                else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
                {
                    inputText = SDL_GetClipboardText();
                    renderText = true;
                }
            }
            //Special text input event
            else if( e.type == SDL_TEXTINPUT )
            {
                //Not copy or pasting
                if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
                {
                    //Append character
                    inputText += e.text.text;
                    renderText = true;
                }
            }
        }

        //Rerender text if needed
        if( renderText )
        {
            //Text is not empty
            if( inputText != "" )
            {
                //Render new text
                SDL->createTextTexture(inputText.c_str(), 450, 450);
            }
            //Text is empty
            else
            {
                //Render space texture
                SDL->createTextTexture(" ", 450, 450);
            }
        }
        //SDL->createImageBackground("hang0.png");
        SDL->createTextTexture(inputText.c_str(), 450, 450);
        SDL->updateScreen();
    }
    
    //Disable text input
    SDL_StopTextInput();
    return inputText;
}
