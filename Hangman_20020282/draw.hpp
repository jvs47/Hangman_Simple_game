//
//  draw.hpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

#ifndef draw_hpp
#define draw_hpp

#include <stdio.h>
#include <string>

std::string getHangPicture(int &badGuessCount);
void clearScreen();
void renderGame(std::string &guessedWord, int &badGuessCount, std::string badGuess);
void printGameOverInfo(std::string &guessedWord, std::string &word, int &badGuessCount);

#endif /* draw_hpp */
