#ifndef HANGMAN_H
#define HANGMAN_H

#include <string>
#include <vector>

class Hangman {
public:
    Hangman(const std::string& word, int maxGuesses);
    void displayState();
    bool guessLetter(char letter);
    bool isGameOver() const;
    bool isWordGuessed() const;
    void saveHighScore(const std::string& playerName);
    void displayHighScores() const;

private:
    std::string word;
    std::string guessedWord;
    int maxGuesses;
    int remainingGuesses;
    std::vector<std::string> highScores;
    
    void updateGuessedWord(char letter);
    void loadHighScores();
};

#endif
