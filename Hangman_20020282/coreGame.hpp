//
//  coreGame.hpp
//  Hangman_20020282
//
//  Created by John Vu on 12/04/2021.
//

#ifndef coreGame_hpp
#define coreGame_hpp

#include <stdio.h>
#include <ctime>
#include <string>
#include <unordered_map>

#include "WindowHeader.h"
#include "SkickSDL.hpp"
#include "utility.hpp"
#include "stringInput.hpp"
using namespace std;

// Hangman Game class
class coreGame {
private:
    const int MAX_BAD_GUESS_Nor = 6;  // Max bad guess of Normal Game
    const int MAX_BAD_GUESS_Hel = 0; // Max bad guess of Hard-core Game
    string category;              // Name of category file
    string catName;               // Name of category title
    int selection = -1;
    int level = -1;               // Level of words
    SkickSDL* SDL;                // Selfmade SDL for easy use
    int playTime;                 // Playing time of Game
    int win;                      // Number of win games
    int loss;                     // Number of loss games
    bool quit;                    // If player want to quit Game
    string word;                  // The random word has to be guessed
    char guessChar;               // Character player pressed
    string guessedWord;           // Guessed word include suggested characters
    string guessedStr;            // Guessed word exclude suggested characters
    int badGuessCount;            // Number of bad guesses made by the player
    int suggested;                // Number of suggested characters
    unsigned long maxSuggest;     // Maximum number of suggestions
    int timeLeft;                 // Left time in second
    string badGuess;              // Bad guessed characters
    time_t startTime;             // The start time of Game
    int animatedTime;             // Time of animations made
    int score;                    // Score
    string playerName;            // player name high score
    string date_time;             // Realtime get high score
    int timePlayed;               // times played
    
public:
    bool playing;                       // Game is playing or not
    coreGame(SkickSDL*);                // initialize Game
    void startGame();                   // initialize new Game
    
    void welcome();                     // welcome
    void renderWelcome();               // render welcome window
    void handleWelcomeEvent();          // handle welcome event
    
    void highScore();                   // highScore
    void renderHighscore();             // render highScore window
    void handleHighscore();             // handle highScore event
    
    void howtoPlay();                   // how to Play game
    
    void chooseCategory();              // Choose the category of random word
    void renderCategory();              // render category window
    void chooseCategoryEvent();         // handle choose category event
    
    void chooseLevel();                 // Choose the level of random word
    void renderLevel();                 // render level window
    void chooseLevelEvent();            // handle choose level event
    
    void initWord();                    // initialize word need guessing
    void hint();                        // get a suggestion
    void updateGuessedWord();           // update guessed word
    void updateHint();                  // update maximum number of suggestions
    bool guessing();                    // determine whether the player is guessing or not
    void guessEvent();                  // handle guessing event
    void handleGuess();                 // handle guessing character
    void updateTime();                  // update playing time
    void badGuessed();                  // handle bad guessed
    
    void gameOver();                    // initialize game over
    void timeplayed();                  // update timePlayed
    
    void checkContinue(SDL_Event);      // check if player want to continue playing game
    void renderGameSDL();               // render playing game window
    
    void renderGameOverSDL(int);        // render game over window
    void createGameOverSDL();           // initialize game over loop for rendering
    
    bool is_highScore();                // check whether high score or not
    void nameHighScore();               // store player name high score
    
    void renderPlane(char, int);        // render flying plane
    void planeEvent(SDL_Event, bool&);  // handle event while the plane is flying

};

#endif /* coreGame_hpp */
