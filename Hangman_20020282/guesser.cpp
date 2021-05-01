//
//  guesser.cpp
//  Hangman_20020282
//
//  Created by John Vu on 30/04/2021.
//

#include "guesser.hpp"
#include <string>
#include <cstdlib>
#include <map>

#include "stringInput.hpp"
#include "util.hpp"

using namespace std;

set<char> Guesser::getRemainingChars(const set<char>& previousGuesses)
{
    set<char> remainingChars;
    for (char c = 'a'; c <= 'z'; c++)
        remainingChars.insert(c);
    for (char c: previousGuesses)
        remainingChars.erase(c);
    return remainingChars;
}

char Guesser::selectRandomChar(const set<char>& s) {
  int r = rand() % s.size();
  set<char>::iterator it = s.begin();
  for (; r != 0; r--) it++;
  return *it;
}

char Guesser::getVowelGuess(const set<char>& remainingChars)
{
    char vowel[] = {'e', 'a', 'o', 'i', 'u'};
    for (char c : vowel) {
        if (remainingChars.find(c) != remainingChars.end())
            return c;
    }
    return 0;
}

bool Guesser::isSuitableWord(const string& word, const string& secretWord, const set<char>& remainingChars)
{
    if (word.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < word.length(); i++) {
        if (secretWord[i] != '-') {
            if (tolower(word[i]) != tolower(secretWord[i])) return false;
        }
        else if (remainingChars.find(word[i]) == remainingChars.end())
             return false;
    }
    return true;
}

vector<string> Guesser::getSuitableWords(const vector<string>& wordList,
                                const string& secretWord,
                                const set<char>& remainingChars)
{
    vector<string> result;
    for (const string& word : wordList)
        if (isSuitableWord(word, secretWord, remainingChars))
            result.push_back(word);
    return result;
}

map<char, int> Guesser::getOccurenceCount(const set<char>& remainingChars, const vector<string>& wordList)
{
    map<char, int> count;
    for (char c: remainingChars) count[c] = 0;

    for (const string& word : wordList) {
        for (char c : word)
            if (count.find(c) != count.end())
                count[c]++;
    }
    return count;
}

char Guesser::getMaxOccurenceChar(const set<char>& remainingChars, const map<char, int>& count)
{
    char best = 0;
    int best_count = 0;
    for (auto p : count)
        if (p.second > best_count) {
            best = p.first;
            best_count = p.second;
        }
    return best;
}

Guesser::Guesser(SkickSDL* SkickSDL): SDL(SkickSDL)
{
    playing = true;
    wordList = readWordListFromFile("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/Dictionary/COM_player.txt");
}

void Guesser::newGame()
{
    quit = false;
    inputWordlength();
    secretWord = string(wordLength, '-');
    incorrectGuess = 0;
    previousGuesses = set<char>();
    stop = false;
}

void Guesser::inputWordlength()
{
    wordLength = 0;
    while(playing && !quit && !stop && wordLength==0)
    {
        renderWordlength();
        handleWordlength();
    }
    
}

void Guesser::renderWordlength()
{
    SDL->createImageBackground("hang0.png");
    SDL->createTextTexture("Choose word length:", 100, 50);
    SDL->createTextTexture("WordLength          :     " + to_string(wordLength), 100, 750);
    SDL->updateScreen();
}

void Guesser::handleWordlength()
{
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            playing = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            playing = false;
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName.length() == 1 && keyName[0] >= '3' && keyName[0] <= '9'){
                wordLength = keyName[0] - '0';
                }
        }
    }
}

string Guesser::getUserAnswer(char guess)
{
    string answer;
    cout << endl << "I guess " << guess<< ", please enter your mask: ";
    answer = stringInput("Please enter mask:","mask");
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}

void Guesser::receiveHostAnswer(char guess, const std::string& m)
{
    if (!isGoodMask(guess, m))
        throw invalid_argument("mistake entering answer");

    previousGuesses.insert(guess);
    if (isAllDash(m)) {
        incorrectGuess ++;
        if (incorrectGuess == MAX_GUESSES) stop = true;
    } else {
        updateSecretWord(m);
        if (isAllNotDash(secretWord)) stop = true;
    }
}

bool Guesser::isGoodMask(char guess, const string& mask)
{
    if (mask.length() != secretWord.length()) return false;
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-') {
            if (mask[i] != guess)
                return false;
            if (secretWord[i] != '-' && secretWord[i] != mask[i])
                return false;
        }
    return true;
}

void Guesser::updateSecretWord(const string& mask)
{
    for (unsigned int i = 0; i < secretWord.length(); i++)
        if (mask[i] != '-')
            secretWord[i] = mask[i];
}

char Guesser::getNextGuess()
{
    set<char> remainingChars = getRemainingChars(previousGuesses);
    if (remainingChars.size() == 0)
        return 0;

    if (isAllDash(secretWord))
        return getVowelGuess(remainingChars);

    vector<string> filteredWordList = getSuitableWords(wordList, secretWord, remainingChars);
    map<char, int> occurenceCount = getOccurenceCount(remainingChars, filteredWordList);
    return getMaxOccurenceChar(remainingChars, occurenceCount);
}

void Guesser::renderGameSDL(char guess) {
    SDL->createImageBackground("hang" + to_string(incorrectGuess) + ".png");
    string guessedWord="";
    for(auto c: previousGuesses)
    {
        guessedWord+=c;
    }
    string to_guess = "I guess ";
    to_guess.push_back(guess);
    SDL->createTextTexture(to_guess, 1200, 300);
    SDL->createTextTexture("WordLength          :     " + to_string(wordLength), 100, 750);
    SDL->createTextTexture("Previous Guesses    :     " + guessedWord, 100, 800);
     
    SDL->createTextTexture("Secret Word         :     " + secretWord, 100, 850);
    SDL->updateScreen();
    SDL_Delay(10);
}

void Guesser::giveUp()
{
    creatgiveUpSDL();
}

void Guesser::rendergiveUpSDL(int imageIndex)
{
    SDL->createImageBackground("hanged" + to_string(imageIndex) + ".png");
    SDL->createTextTexture("I give up, hang me", 100, 750);
    SDL->createTextTexture("Press 'Enter' to keep playing, 'ESC' to exit.", 100, 850);
    SDL->updateScreen();
}

void Guesser::creatgiveUpSDL()
{
    int imageIndex = 0;
    while (!quit) {
        SDL_Event e;
        checkContinue(e);
        rendergiveUpSDL(imageIndex);
        SDL_Delay(200);
        ++imageIndex %= 4;
    }
}

void Guesser::gameOver()
{
    createGameOverSDL();
}

void Guesser::renderGameOverSDL(int imageIndex) {
    

//    if (timeLeft <= 0)
//        SDL->createTextTexture("Time Up!!!", 1200, 5);
    bool isLosing = (incorrectGuess == MAX_GUESSES);
    
    string status = (isLosing ? "free" : "hanged");
    
    SDL->createImageBackground(status + to_string(imageIndex) + ".png");
    
    
    if (!isLosing)
        SDL->createTextTexture("Congrats!!! You are free.", 100, 750);
    else
    {
        SDL->createTextTexture("Game Over!!! You are hanged!", 100, 750);
        SDL->createTextTexture("I lost :(. My best word is: " + secretWord, 100, 800);
    }
    
    SDL->createTextTexture("Press 'Enter' to keep playing, 'ESC' to exit.", 100, 850);
    SDL->updateScreen();
}


void Guesser::createGameOverSDL() {
    int imageIndex = 0;
    while (!quit) {
        SDL_Event e;
        checkContinue(e);
        renderGameOverSDL(imageIndex);
        SDL_Delay(200);
        ++imageIndex %= 4;
    }
}

void Guesser::checkContinue(SDL_Event e) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
            playing = false;
            quit = true;
        }
        else if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_RETURN ||e.key.keysym.sym == SDLK_RETURN2 ||e.key.keysym.sym == SDLK_KP_ENTER)) {
            playing = true;
            quit = true;
        }
    }
}
