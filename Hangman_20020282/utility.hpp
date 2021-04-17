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
#include <vector>

struct playerScore
{
    std::string name;
    int score;
    int time;
    int maxScore;
    playerScore(){};
    playerScore(std::string _n, int _s, int _t);
    
};

std::string normalize(const std::string s);
std::string chooseWord(const std::string fileName, int level);
bool contains(std::string word, char guess);
void storeHighScore(std::string playerName, int score, int timeplayed, int win, int loss, std::string date_time);
int calScore(int level, int suggested);

void getHighScore();
int maxHighScore();
std::string getTime();
#endif /* utility_hpp */
