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
    ifstream fileIn;
    fileIn.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Dictionary/" + fileName);
    if (!fileIn.is_open())
    {
        cout << "Cannot open file " << fileName << endl;
        return "";
    }
    string data;
    getline(fileIn, data);
    while (!fileIn.eof()) {
        string line;
        getline(fileIn, line);
        if (fileIn && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    srand( static_cast<unsigned int>(time(nullptr)));
   
    fileIn.close();
    unsigned long n = vocabulary.size();
    cout << "vocabulary size = " << n << endl;
    string word = vocabulary[rand() % n];
    if(level != 2)
        return n > 0 ? ((word.length() > 6 && level) || (word.length() <= 6 && !level) ? word : chooseWord(fileName, level)) : "";
    else
        return n>0? word : "";
}

bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}

void storeHighScore(string playerName, int score, int timeplayed, int win, int loss)
{
    ofstream fileOut;
    fileOut.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Score/playerScore.txt", std::ios::app);
    if(!fileOut.is_open())
    {
        cout << "Cannot open Score file\n";
        return;
    }
    string line = normalize(playerName) + ' ' + to_string(score) + ' ' + to_string(timeplayed) + ' ' +to_string(win) + '-' + to_string(loss);
    fileOut << line << endl;
    fileOut.close();
}

int calScore(int level, int suggested)
{
    return (level+1)*100 - 50*suggested;
}

int getHighScore()
{
    ifstream fileIn;
    fileIn.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Score/playerScore.txt", std::ios::in);
    if(!fileIn.is_open())
    {
        cout << "Cannot open Score file\n";
        return -1;
    }
    string line;
    getline(fileIn, line);
    
    vector<string> playerName;
    vector<int> score;
    vector<int> timeplayed;
    while(!fileIn.eof())
        {
            string _playerName;
            fileIn >> _playerName;
            int _score;
            fileIn >> _score;
            int _timeplayed;
            fileIn >> _timeplayed;
            playerName.push_back(_playerName);
            score.push_back(_score);
            timeplayed.push_back(_timeplayed);
        }
    return *max_element(score.begin(), score.end());
}
