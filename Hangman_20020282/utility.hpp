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
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

//player Score struct
struct playerScore
{
    std::string name;   
    int score;
    int time;
    int win;
    int loss;
    std::string recored;
    playerScore(){};
    ~playerScore(){};
    playerScore(std::string _n, int _s, int _t, int _w, int _l, std::string _r);
    
};

//Word utility
std::string normalize(const std::string);
std::string chooseWord(const std::string, int);
bool contains(std::string, char);

//Handle Score
void storeHighScore(std::string, int, int, int, int, std::string);
int calScore(int, int);
std::vector<playerScore> getHighScore();
int maxHighScore();
std::string getTime();

bool cmp(const playerScore&, const playerScore&);
bool cmp2(const playerScore&, const playerScore&);

//Padding string
std::string paddingStr(const playerScore&, int&);
#endif /* utility_hpp */
