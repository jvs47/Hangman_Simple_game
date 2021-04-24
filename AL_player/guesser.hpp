//
//  guesser.hpp
//  Hangman_20020282
//
//  Created by John Vu on 22/04/2021.
//

#ifndef guesser_hpp
#define guesser_hpp

#include <stdio.h>
#pragma once

#include <string>
#include <set>
#include <vector>
#include <map>
#include "SkickSDL.hpp"

class Guesser
{
private:
    string secretWord;
    int incorrectGuess;
    set<char> previousGuesses;
    vector<string> wordList;
    SkickSDL* SDL;
    bool quit = false;
    int wordLength;
    char guess;
private:
    bool isGoodMask(char guess, const string& mask);
    void updateSecretWord(const string& mask);
    set<char> getRemainingChars(const set<char>& previousGuesses);
    char getVowelGuess(const set<char>& remainingChars);
    char selectRandomChar(const set<char>& s);
    map<char, int> getOccurenceCount(const set<char>& remainingChars, const vector<string>& wordList);
    char getMaxOccurenceChar(const set<char>& remainingChars, const map<char, int>& count);
    bool isSuitableWord(const string& word, const string& secretWord, const set<char>& remainingChars);
    vector<string> getSuitableWords(const vector<string>& wordList, const string& secretWord, const set<char>& remainingChars);
public:
    const int MAX_GUESSES = 7;
    bool playing;
public:
    Guesser(SkickSDL* );
    void getUserWordLength();
    void newGame();
    void receiveHostAnswer(char guess, const string& mask);
    char getNextGuess();
    string getUserAnswer(char guess);
    int getIncorrectGuess() const { return incorrectGuess; }
    set<char> getPreviousGuesses() const { return previousGuesses; }
    string getSecretWord() const { return secretWord; }
    bool isGuessing();
    void gameOver();
    void renderGameSDL();               // render playing game window
    void renderGameOverSDL(int);        // render game over window
    void createGameOverSDL();           // initialize game over loop for rendering
    void checkContinue(SDL_Event);
    
};


#endif /* guesser_hpp */
