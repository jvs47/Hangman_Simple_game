//
//  util.hpp
//  Hangman_20020282
//
//  Created by John Vu on 30/04/2021.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "SkickSDL.hpp"

//Word utility
std::string normalizeWord(const std::string);
int generateRandomNumber(int, int);
bool isCharInWord(char, std::string);
std::vector<std::string> readWordListFromFile(const std::string&);
bool isAllDash(const std::string&);
bool isAllNotDash(const std::string&);

//input mask
std::string maskInput(SkickSDL*);

#endif /* util_hpp */
