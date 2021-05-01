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

std::string normalizeWord(const std::string s);
int generateRandomNumber(int min, int max);
bool isCharInWord(char ch, std::string word);
std::vector<std::string> readWordListFromFile(const std::string& filePath);
bool isAllDash(const std::string& s);
bool isAllNotDash(const std::string& s);
void clearScreen();

#endif /* util_hpp */
