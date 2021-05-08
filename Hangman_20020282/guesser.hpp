//
//  guesser.hpp
//  Hangman_20020282
//
//  Created by John Vu on 30/04/2021.
//

#ifndef guesser_hpp
#define guesser_hpp

#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include <map>

#include "WindowHeader.h"
#include "SkickSDL.hpp"
using namespace std;

class Guesser
{
private:
    string secretWord;
    int incorrectGuess;
    int wordLength;
    set<char> previousGuesses;
    bool stop;
    vector<string> wordList;
    SkickSDL* SDL;
    bool quit;
private:
    bool isGoodMask(char, const string&);
    void updateSecretWord(const string&);
    set<char> getRemainingChars(const set<char>&);
    char getVowelGuess(const set<char>&);
    char selectRandomChar(const set<char>&);
    map<char, int> getOccurenceCount(const set<char>&, const vector<string>& wordList);
    char getMaxOccurenceChar(const set<char>&, const map<char, int>&);
    bool isSuitableWord(const string&, const string& , const set<char>&);
    vector<string> getSuitableWords(const vector<string>& , const string&, const set<char>& );
public:
    const int MAX_GUESSES = 6;
public:
    bool playing;
    Guesser(SkickSDL*);
    void newGame();
    void inputWordlength();
    void handleWordlength();
    void renderWordlength();
    string getUserAnswer(char );
    void receiveHostAnswer(char , const string& );
    void getMask(string&, char);
    void handleMask(SDL_Event, string&, bool&, char);
    char getNextGuess();

    int getIncorrectGuess() const { return incorrectGuess; }
    set<char> getPreviousGuesses() const { return previousGuesses; }
    bool isStop() const { return stop; }
    string getSecretWord() const { return secretWord; }
    
    void giveUp();
    void creatgiveUpSDL();
    void rendergiveUpSDL(int);
    void gameOver();                    // initialize game over
    void checkContinue(SDL_Event);      // check if player want to continue playing game
    void renderGameSDL(char);               // render playing game window
    void renderGameOverSDL(int);        // render game over window
    void createGameOverSDL();           // initialize game over loop for rendering

};

#endif /* guesser_hpp */
