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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("%s", Mix_GetError());
    }
    playing = true;
    win = 0;
    loss = 0;
    score = 0;
    timePlayed = 0;
    selection = -1;
    

    startSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/gong.wav");
    correctSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/phew.wav");
    incorrectSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/rope-tighten.wav");
    deadSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/dead.wav");
    aliveSFX = Mix_LoadWAV("/Volumes/DATA/C++/Hangman_20020282/Hangman_20020282/SFX/yeehaw.wav");
    

}

void coreGame::welcome()
{
    while( playing && !quit && selection == -1)
    {
        renderWelcome();
        handleWelcomeEvent();
        highScore();
        howtoPlay();
    }
}

void coreGame::renderWelcome()
{
    SDL->createImageBackground("intro.png");
    SDL->createTextTexture("__PLAYER MODE__", 500, 150);
    SDL->createTextTexture("1. New game", 500, 300);
    SDL->createTextTexture("2. High score", 500, 350);
    SDL->createTextTexture("3. How to play", 500, 400);
    SDL->createTextTexture("4. Options", 500, 450);
    SDL->createTextTexture("Press ESC to Quit", 500, 600);
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
            {
                playing = false;
                selection = -1;
            }
        } else if (event.type == SDL_KEYUP) {
            string keyName = SDL_GetKeyName(event.key.keysym.sym);
            if (keyName.length() == 1 && keyName[0] >= '1' && keyName[0] <= '4')
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
                    case '4':
                    {
                        playing = true;
                        quit = false;
                        selection = 3;
                    }
                        break;
                }
        }
    }
}

void coreGame::howtoPlay()
{
    if(selection == 2)
    {
        system("open https://www.youtube.com/watch?v=leW9ZotUVYo&ab_channel=wikiHow");
        selection = -1;
    }
}

void coreGame::startGame()
{
    quit = false;
    //system("clear");

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

void coreGame::highScore()
{
    while(selection == 1 && playing && !quit)
    {
        renderHighscore();
        handleHighscore();
    }
}

void coreGame::renderHighscore()
{
    SDL->createImageBackground("hang0.png");
    SDL->createTextTexture("____HIGH SCORE___", 300, 50);
    SDL->createTextTexture("Rank PlayerName Score Times Win Loss                   Time_recored", 150, 200);
    vector<playerScore> p = getHighScore();
    unsigned long n =  p.size();
    for(int i = 1; i<=n; i++)
    {
        playerScore p1 = p[i-1];
        string line = paddingStr(p1, i);
        SDL->createTextTexture(line, 150, 200+50*i);
    }
    SDL->createTextTexture("Press Enter to go back, ESC to Quit", 180, 800);
    SDL->updateScreen();
}

void coreGame::handleHighscore()
{
    SDL_Event event;
    if (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            playing = false;
            quit = true;
        } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
            playing = false;
        } else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_RETURN ||event.key.keysym.sym == SDLK_RETURN2 ||event.key.keysym.sym == SDLK_KP_ENTER)) {
            playing = true;
            quit = false;
            selection = -1;
        }
    }
}

void coreGame::chooseCategory() {
    category = "";
    while (category == "" && playing && !quit && selection == 0) {
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
    SDL->createImageBackground("intro.png");
    SDL->createTextTexture("Choose word category:", 500, 150);
    SDL->createTextTexture("1. Animals", 550, 250);
    SDL->createTextTexture("2. City", 550, 300);
    SDL->createTextTexture("3. Clothes", 550, 350);
    SDL->createTextTexture("4. Jobs", 550, 400);
    SDL->createTextTexture("5. Fruits", 550, 450);
    SDL->createTextTexture("6. Evironment", 550, 500);
    SDL->createTextTexture("5. Family", 550, 550);
    SDL->updateScreen();
}

void coreGame::chooseLevel() {
    level = -1;
    while (level == -1 && playing && !quit && selection == 0) {
        renderLevel();
        chooseLevelEvent();
    }
    Mix_PlayChannel(1, startSFX, 0);
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
    SDL->createImageBackground("intro.png");
    SDL->createTextTexture("Category: " + catName, 500, 150);
    SDL->createTextTexture("Choose word Level:", 500, 200);
    SDL->createTextTexture("1. Easy", 550, 300);
    SDL->createTextTexture("2. Hard", 550, 350);
    SDL->createTextTexture("3. Hell (Zero try)", 550, 400);
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
        Mix_PlayChannel(1, correctSFX, 0);
    } else if (!contains(badGuess, guessChar)) {
        badGuessed();
        renderPlane(guessChar, 0);
        if(badGuessCount<MAX_BAD_GUESS_Nor)
        Mix_PlayChannel(1, incorrectSFX, 0);
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
        {
            loss++;
            if(!quit)
            Mix_PlayChannel(1, deadSFX, 0);
        }
    else
    {   win++;
        score += calScore(level,suggested);
        if(!quit)
        Mix_PlayChannel(1, aliveSFX, 0);
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
    if(playing)
    {
        SDL->createImageBackground("hang" + to_string(badGuessCount+1) + ".png");
        SDL->createTextTexture("Time : " + to_string(timeLeft) +"s", 740, 5);
        SDL->createTextTexture("Win  : " + to_string(win), 740, 45);
        SDL->createTextTexture("Loss : " + to_string(loss), 740, 85);
        SDL->createTextTexture("Score: " + to_string(score), 740, 125);
        SDL->createTextTexture("Current Guess    :     " + guessedWord, 100, 750);
        SDL->createTextTexture("Bad Guesses      :     " + badGuess, 100, 800);
        SDL->createTextTexture("Used suggestions :     " + to_string(suggested) + "/" + to_string(maxSuggest) + "   (Press 'Space')", 100, 850);
        SDL->updateScreen();
        SDL_Delay(10);
        
    }
}

void coreGame::renderGameOverSDL(int imageIndex) {
    string status = (guessedWord == word ? "free" : "hanged");
    SDL->createImageBackground(status + to_string(imageIndex) + ".png");
    
    if (timeLeft <= 0)
        SDL->createTextTexture("Time Up!!!", 740, 5);
    
    SDL->createTextTexture("Win  : " + to_string(win), 740, 45);
    SDL->createTextTexture("Loss : " + to_string(loss), 740, 85);
    SDL->createTextTexture("Score: " + to_string(score), 740, 125);
    
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
        SDL_Delay(180);
        ++imageIndex %= 4;
    }
}

bool coreGame::is_highScore()
{
    int maxScore = maxHighScore();
    if(score>=maxScore)
        return 1;
    return 0;
}
void coreGame::nameHighScore()
{
    playerName = stringInput("Congratulation!!!","New High Score: ", "intput name");
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
            else
                continue;
        }
        else if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_RETURN ||e.key.keysym.sym == SDLK_RETURN2 ||e.key.keysym.sym == SDLK_KP_ENTER)) {
            playing = true;
            quit = true;
        }
    }
}
