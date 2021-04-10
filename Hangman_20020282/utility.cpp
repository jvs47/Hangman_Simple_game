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

string normalize(const string& s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

string chooseWord(const string& fileName)
{
    vector<string> vocabulary;
    ifstream file(fileName);
    //file.open(fileName);
    if (!file.is_open())
        return "";
    
    while (!file.eof()) {
        string line;
        getline(file, line);
        if (file && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    
    unsigned long n = vocabulary.size();
    cout << "vocabulary size = " << n << endl;
    file.close();
    return n > 0 ? vocabulary[rand() % n] : "";
}

bool contains(string &word, char &guess)
{
    return (word.find(guess) != string::npos);
}
