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
    << setfill(' ') << setw(5) << timeplayed << ' '
    << setfill(' ') << setw(3) << win << ' '
    << setfill(' ') << setw(4) << loss << ' '
    << setfill(' ') << setw(30) << date_time;
    fileOut.close();
}

int calScore(int level, int suggested)
{
    return (level+1)*100 - 50*suggested;
}

playerScore::playerScore(std::string _n, int _s, int _t, int _w, int _l, std::string _r): name(_n), score(_s), time(_t), win(_w), loss(_l), recored(_r){};

bool cmp(const playerScore& p1, const playerScore& p2)
{
    return p1.score < p2.score;
}

vector<playerScore> getHighScore()
{
    vector<playerScore> p(0);
    ifstream fileIn;
    fileIn.open("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Score/playerScore.txt", std::ios::in);
    if(!fileIn.is_open())
    {
        cout << "Cannot open Score file\n";
        return p;
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
        int _win;
        fileIn >> _win;
        int _loss;
        fileIn >> _loss;
        string _recored;
        getline(fileIn, _recored);
        fileIn.ignore();
        playerScore p1 = playerScore(_playerName, _score, _timeplayed, _win, _loss, _recored);
        p.push_back(p1);
    }
    sort(p.begin(), p.end(), cmp);
    return p;
}

int maxHighScore()
{
    vector<playerScore> p = getHighScore();
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

string paddingStr(const playerScore &p, int &i)
{
    string _i = to_string(i);
    _i.insert(_i.begin(), 4 - _i.length(), ' ');
    string name = p.name;
    name.insert(name.begin(), 10-name.length(), ' ');
    string score = to_string(p.score);
    score.insert(score.begin(), 5-score.length(),' ');
    string time = to_string(p.time);
    time.insert(time.begin(), 5-time.length(), ' ');
    string win = to_string(p.win);
    win.insert(win.begin(), 3-win.length(), ' ');
    string loss = to_string(p.loss);
    loss.insert(loss.begin(), 4-loss.length(), ' ');
    string recored = p.recored;
    recored.insert(recored.begin(), 30-recored.length(), ' ');
    string _re = _i + ' ' +name + ' '+score + ' '+time + ' '+win + ' '+loss +' '+recored;
    return _re;
}
