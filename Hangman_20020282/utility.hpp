//
//  utility.hpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <string>


std::string normalize(const std::string s);
std::string chooseWord(const std::string fileName, int level);
bool contains(std::string word, char guess);
void storeHighScore(std::string playerName, int score, int timeplayed, int win, int loss);
int calScore(int level, int suggested);
int getHighScore();
#endif /* utility_hpp */
