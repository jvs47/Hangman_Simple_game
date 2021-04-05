//
//  utility.hpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

//#ifndef utility_hpp
//#define utility_hpp
//
//#include <stdio.h>

//#endif /* utility_hpp */
#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <string>

std::string normalize(const std::string& s);
std::string chooseWord(const std::string& fileName);
bool contains(std::string word, char guess);

#endif // __UTILITY_H__
