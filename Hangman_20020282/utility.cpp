//
//  utility.cpp
//  Hangman_20020282
//
//  Created by John Vu on 05/04/2021.
//

#include "utility.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

string normalize(const string s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

string chooseWord(const string fileName, int level)
{
    vector<string> vocabulary;
    ifstream file;
    file.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Dictionary/" + fileName);
    if (!file.is_open())
        return "";
    int n ;
    file >> n;
    cout << "vocabulary size = " << n << endl;
    string data;
    getline(file, data);
    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    srand( static_cast<unsigned int>(time(nullptr)));
   
    file.close();
    
    int i = rand() % n;
    string word = vocabulary[i];
    return n>0? ((word.length() > 5 && level) || (word.length() < 5 && !level) ? word : chooseWord(fileName, level)) : "";
}

bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}
