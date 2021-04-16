//
//  coreGame.cpp
//  Hangman_20020282
//
//  Created by John Vu on 12/04/2021.
//

#include "coreGame.hpp"
#include <ctime>
#include <unordered_map>
#include <curses.h>

#include "SkickSDL.hpp"
#include "utility.hpp"
#include "stringInput.hpp"
using namespace std;

coreGame::coreGame(SkickSDL* SkickSDL) : SDL(SkickSDL) {
    playing = true;
    win = 0;
    loss = 0;
    score = 0;
    timePlayed = 0;
}

void coreGame::startGame() {
    quit = false;
    system("clear");
    welcome();
    chooseCategory();
    chooseLevel();
    initWord();
    guessedWord = string(word.length(), '-');
    guessChar = ' ';
    badGuessCount = 0;
    maxSuggest = 10;
    badGuess = "";
    suggested = 0;
    guessedStr = "";
    animatedTime = 0;
    time(&startTime);
    for (unsigned int i = 0; i < word.length(); i++)
    if (word[i] == ' ')
        guessedWord[i] = ' ';
    updateHint();
}

void coreGame::welcome()
{
    while(selection == -1 && playing && !quit)
    {
        renderWelcome();
        handleWelcomeEvent();
    }
}

void coreGame::renderWelcome()
{
    SDL->createImageBackground("hang0.png");
    SDL->createTextTexture("WELCOME TO HANGMAN", 100, 50);
    SDL->createTextTexture("1. New game", 150, 100);
    SDL->createTextTexture("2. High score", 150, 150);
    SDL->createTextTexture("3. How to play", 150, 200);
    SDL->createTextTexture("Press ESC to Quit", 150, 400);
    SDL->updateScreen();
}

void coreGame::handleWelcomeEvent()
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
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '5')
                switch (keyName[0]) {
                    case '1':
                    {
                        playing = true;
                        quit = false;
                        selection = 0;
                    }
                        break;
                    case '2':
                    {
                        playing = true;
                        quit = false;
                        selection = 1;
                    }
                        break;
                    case '3':
                    {
                        playing = true;
                        quit = false;
                        selection = 2;
                    }
                        break;
                }
        }
    }
}

void coreGame::chooseCategory() {
    category = "";
    while (category == "" && playing && !quit) {
        renderCategory();
        chooseCategoryEvent();
    }
}

void coreGame::chooseCategoryEvent() {
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            playing = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            playing = false;
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '7')
                switch (keyName[0]) {
                    case '1':
                        category = "Animals.txt";
                        catName = "Animals";
                        break;
                    case '2':
                        category = "City.txt";
                        catName = "City";
                        break;
                    case '3':
                        category = "Clothes.txt";
                        catName = "Clothes";
                        break;
                    case '4':
                        category = "Jobs.txt";
                        catName = "Jobs";
                        break;
                    case '5':
                        category = "Fruits.txt";
                        catName = "Fruits";
                        break;
                    case '6':
                        category = "Evironment.txt";
                        catName = "Environment";
                        break;
                    case '7':
                        category = "Family.txt";
                        catName = "Family";
                        break;
                }
        }
    }
}

void coreGame::renderCategory() {
    SDL->createImageBackground("hang0.png");
    SDL->createTextTexture("Choose word category:", 100, 50);
    SDL->createTextTexture("1. Animals", 150, 100);
    SDL->createTextTexture("2. City", 150, 150);
    SDL->createTextTexture("3. Clothes", 150, 200);
    SDL->createTextTexture("4. Jobs", 150, 250);
    SDL->createTextTexture("5. Fruits", 150, 300);
    SDL->createTextTexture("6. Evironment", 150, 350);
    SDL->createTextTexture("5. Family", 150, 400);
    SDL->updateScreen();
}

void coreGame::chooseLevel() {
    level = -1;
    while (level == -1 && playing && !quit) {
        renderLevel();
        chooseLevelEvent();
    }
}

void coreGame::chooseLevelEvent() {
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            playing = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            playing = false;
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '3')
                switch (keyName[0]) {
                    case '1':
                    {
                        level = 0;
                        playTime = 90;
                    }
                        break;
                    case '2':
                    {
                        level = 1;
                        playTime = 150;
                    }
                        break;
                    case '3':
                    {
                        level = 2;
                        playTime = 200;
                    }
                        break;
                }
        }
    }
}

void coreGame::renderLevel() {
    SDL->createImageBackground("hang0.png");
    SDL->createTextTexture("Category: " + catName, 100, 50);
    SDL->createTextTexture("Choose word Level:", 100, 100);
    SDL->createTextTexture("1. Easy", 150, 150);
    SDL->createTextTexture("2. Hard", 150, 200);
    SDL->createTextTexture("3. Hell (Zero try)", 150, 250);
    SDL->updateScreen();
}

void coreGame::renderPlane(char guessedChar, int num) {
    time_t startT, endT;
    time(&startT);
    int i = -300;
    bool skip = false;
    while (i < 1000 && !skip) {
        SDL_Event event;
        planeEvent(event, skip);
        SDL->createImageBackground("hang0.png");
        SDL->createImage("plane.png", i, 0);
        SDL->createTextTexture(string("There ") + (num == 1 ? "is " : "are ") + to_string(num) + " of " + guessedChar, i + 165, 215);
        SDL->createTextTexture("Press 'Space' to skip", 300, 850);
        SDL->updateScreen();
        i += 5;
    }
    time(&endT);
    animatedTime += difftime(endT, startT);
}

void coreGame::planeEvent(SDL_Event e, bool& skip) {
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
            skip = true;
        if (e.type == SDL_QUIT) {
            playing = false;
            quit = true;
            skip = true;
        }
    }
}

void coreGame::initWord() {
    word = chooseWord(category, level);
    if (word.empty()) {
        cout << "No word available in " << category << endl;
        playing = false;
        quit = true;
    }
}

void coreGame::guessEvent() {
    SDL_Event event;
    guessChar = ' ';
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            playing = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            playing = false;
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName == "Escape")
                playing = false;
            else if (keyName == "Space")
                guessChar = '$';
            else if (keyName.length() == 1 && keyName[0] >= 'A' && keyName[0] <= 'Z')
                guessChar = keyName[0]+32;
        }
    }
}

void coreGame::handleGuess() {
    if (guessChar == ' ') return;
    if (guessChar == '$')
        hint();
    else if (contains(guessedStr, guessChar))
        return;
    else if (contains(word, guessChar)) {
        updateGuessedWord();
        updateHint();
    } else if (!contains(badGuess, guessChar)) {
        badGuessed();
        renderPlane(guessChar, 0);
    }
}

void coreGame::badGuessed() {
    badGuessCount++;
    badGuess += guessChar;
    guessedStr += guessChar;
}

bool coreGame::guessing() {
    if(level != 2)
        return badGuessCount < MAX_BAD_GUESS_Nor && guessedWord != word && timeLeft > 0 && playing;
    else
    {
        return badGuessCount < MAX_BAD_GUESS_Hel && guessedWord != word && timeLeft > 0 && playing;
    }
}

void coreGame::updateTime() {
    time_t now;
    time(&now);
    timeLeft = playTime - difftime(now, startTime) + animatedTime;
}

void coreGame::gameOver() {
    if (guessedWord != word)
        loss++;
    else
    {   win++;
        score += calScore(level,suggested);
    }
    createGameOverSDL();
}

void coreGame::timeplayed()
{
    timePlayed = win+loss;
}

void coreGame::updateGuessedWord() {
    unsigned long n = guessedWord.length();
    int numOfChar = 0;
    for (int i = 0; i < n; i++) {
        if (word[i] == guessChar) {
            guessedWord[i] = guessChar;
            numOfChar++;
        }
    }
    guessedStr += guessChar;
    renderPlane(guessChar, numOfChar);
}

void coreGame::updateHint() {
    if (suggested < maxSuggest) {
        unsigned long suggest = 0;
        unsigned long n = guessedWord.length();
        unordered_map<char, int> m;
        for (int i = 0; i < n; i++)
        if (guessedWord[i] == '-')
            m[word[i]]++;
        suggest = m.size();
        maxSuggest = suggest / 2;
    }
    if (suggested > maxSuggest) maxSuggest = suggested;
}

void coreGame::hint() {
    if (suggested < maxSuggest) {
        suggested++;
        while (true) {
            int i = rand() % guessedWord.length();
            if (guessedWord[i] == '-') {
                guessChar = word[i];
                updateGuessedWord();
                break;
            }
        }
    }
}

void coreGame::renderGameSDL() {
    SDL->createImageBackground("hang" + to_string(badGuessCount) + ".png");
    SDL->createTextTexture("Time : " + to_string(timeLeft) +"s", 750, 5);
    SDL->createTextTexture("Win  : " + to_string(win), 750, 45);
    SDL->createTextTexture("Loss : " + to_string(loss), 750, 85);
    SDL->createTextTexture("Score: " + to_string(score), 750, 125);
    SDL->createTextTexture("Current Guess    :     " + guessedWord, 100, 750);
    SDL->createTextTexture("Bad Guesses      :     " + badGuess, 100, 800);
    SDL->createTextTexture("Used suggestions :     " + to_string(suggested) + "/" + to_string(maxSuggest) + "   (Press 'Space')", 100, 850);
    SDL->updateScreen();
    SDL_Delay(10);
}

void coreGame::renderGameOverSDL(int imageIndex) {
    string status = (guessedWord == word ? "free" : "hanged");
    SDL->createImageBackground(status + to_string(imageIndex) + ".png");
    
    if (timeLeft <= 0)
        SDL->createTextTexture("Time Up!!!", 750, 5);
    
    SDL->createTextTexture("Win  : " + to_string(win), 750, 45);
    SDL->createTextTexture("Loss : " + to_string(loss), 750, 85);
    SDL->createTextTexture("Score: " + to_string(score), 750, 125);
    
    if (guessedWord == word)
        SDL->createTextTexture("Congrats!!! You are free.", 100, 750);
    else
        SDL->createTextTexture("Game Over!!! You are hanged!", 100, 750);
    
    SDL->createTextTexture("Correct word: " + word, 100, 800);
    SDL->createTextTexture("Press 'Enter' to keep playing, 'ESC' to exit.", 100, 850);
    SDL->updateScreen();
    
    
}

void coreGame::createGameOverSDL() {
    int imageIndex = 0;
    while (!quit) {
        SDL_Event e;
        checkContinue(e);
        renderGameOverSDL(imageIndex);
        SDL_Delay(200);
        ++imageIndex %= 4;
    }
}

bool coreGame::is_highScore()
{
    int highScore = getHighScore();
    if(score>highScore)
        return 1;
    return 0;
}
void coreGame::nameHighScore()
{
    playerName = stringInput();
    date_time = getTime();
    timeplayed();
    storeHighScore(playerName, score, timePlayed, win, loss, date_time);
}

void coreGame::checkContinue(SDL_Event e) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)) {
            playing = false;
            quit = true;
            if(is_highScore())
                nameHighScore();
        }
        else if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_RETURN ||e.key.keysym.sym == SDLK_RETURN2 ||e.key.keysym.sym == SDLK_KP_ENTER)) {
            playing = true;
            quit = true;
        }
    }
}
