//
//  util.hpp
//  Hangman_20020282
//
//  Created by John Vu on 30/04/2021.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#pragma once

#include <vector>
#include <string>

std::string normalizeWord(const std::string);
int generateRandomNumber(int, int);
bool isCharInWord(char, std::string);
std::vector<std::string> readWordListFromFile(const std::string&);
bool isAllDash(const std::string&);
bool isAllNotDash(const std::string&);
void clearScreen();

#endif /* util_hpp */
