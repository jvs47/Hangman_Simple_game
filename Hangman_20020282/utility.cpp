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
#include <iomanip>
using namespace std;

std::vector<playerScore> p;

string normalize(const string s)
{
    string news = s;
    transform(s.begin(), s.end(), news.begin(), ::tolower);
    return news;
}

string chooseWord(const string fileName, int level)
{
    vector<string> vocabulary;
    vector<string> vocabulary_easy;
    vector<string> vocabulary_hard;
    ifstream fileIn;
    fileIn.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Dictionary/" + fileName);
    if (!fileIn.is_open())
    {
        cout << "Cannot open file " << fileName << endl;
        return "";
    }
    while (!fileIn.eof()) {
        string line;
        getline(fileIn, line);
        if (fileIn && !line.empty())
            vocabulary.push_back(normalize(line));
    }
    srand( static_cast<unsigned int>(time(nullptr)));
   
    fileIn.close();
    unsigned long n = vocabulary.size();
    if(n==0) return "";
    cout << "vocabulary size = " << n << endl;
    
    for(unsigned long i = 0; i<n; i++)
    {
        if(vocabulary[i].length()<6)
            vocabulary_easy.push_back(vocabulary[i]);
        else
            vocabulary_hard.push_back(vocabulary[i]);
    }
    
    if(level != 2)
        {
            if(!level)
            {
                unsigned long easy = vocabulary_easy.size();
                string word = vocabulary_easy[rand() % easy];
                return word;
            }
            else
            {
                unsigned long hard = vocabulary_hard.size();
                string word = vocabulary_hard[rand() % hard];
                return word;
            }
        }
    else
    {
        string word = vocabulary[rand() % n];
        return word;
    }
}

bool contains(string word, char guess)
{
    return (word.find(guess) != string::npos);
}

void storeHighScore(string playerName, int score, int timeplayed, int win, int loss, string date_time)
{
    ofstream fileOut;
    fileOut.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Score/playerScore.txt", std::ios::app);
    if(!fileOut.is_open())
    {
        cout << "Cannot open Score file\n";
        return;
    }
    //string norName = normalize(playerName)+ ' ' + to_string(score) + ' ' + to_string(timeplayed) + ' ' +to_string(win) + '-' + to_string(loss);
    fileOut << setfill(' ') << setw(10) << normalize(playerName) << ' '
            << setfill(' ') << setw(5) << score << ' '
    << setfill(' ') << setw(10) << timeplayed << ' '
    << setfill(' ') << setw(3) << win << ' '
    << setfill(' ') << setw(4) << loss << ' '
    << setfill(' ') << setw(30) << date_time;
    fileOut.close();
}

int calScore(int level, int suggested)
{
    return (level+1)*100 - 50*suggested;
}

playerScore::playerScore(std::string _n, int _s, int _t): name(_n), score(_s), time(_t){};

bool cmp(const playerScore& p1, const playerScore& p2)
{
    return p1.score < p2.score;
}


void getHighScore()
{
    ifstream fileIn;
    fileIn.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Score/playerScore.txt", std::ios::in);
    if(!fileIn.is_open())
    {
        cout << "Cannot open Score file\n";
        return;
    }
    string line;
    getline(fileIn, line);
    
    
    while(!fileIn.eof())
        {
            string _playerName;
            fileIn >> _playerName;
            int _score;
            fileIn >> _score;
            int _timeplayed;
            fileIn >> _timeplayed;
            playerScore p1 = playerScore(_playerName, _score, _timeplayed);
            p.push_back(p1);
            getline(fileIn,line);
        }
}

int maxHighScore()
{
    auto maxHigh = *max_element(p.begin(), p.end(), cmp);
    return maxHigh.score;
}

string getTime()
{
    // current date and time on the current system
       time_t now = time(0);

       // convert now to string form
       string date_time = ctime(&now);
    return date_time;
}
