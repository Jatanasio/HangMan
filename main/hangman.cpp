#include "hangman.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor to initialize the game with a word and maximum guesses
Hangman::Hangman(const std::string& word, int maxGuesses) 
    : word(word), maxGuesses(maxGuesses), remainingGuesses(maxGuesses), guessedWord(word.length(), '_') {
    loadHighScores();
}

// Display the current state of the word (guessed so far)
void Hangman::displayState() {
    std::cout << "Word: " << guessedWord << std::endl;
    std::cout << "Remaining guesses: " << remainingGuesses << std::endl;
}

// Handle a letter guess
bool Hangman::guessLetter(char letter) {
    bool letterFound = false;

    // Check each letter of the word
    for (size_t i = 0; i < word.length(); ++i) {
        if (word[i] == letter) {
            guessedWord[i] = letter;  // Reveal the letter in the guessed word
            letterFound = true;        // Mark that the letter was found
        }
    }

    if (!letterFound) {
        --remainingGuesses;  // Decrement guesses if the letter was not found
    }

    // Return true if the letter was found, false otherwise
    return letterFound;
}


// Check if the game is over (either won or lost)
bool Hangman::isGameOver() const {
    return remainingGuesses <= 0 || isWordGuessed();
}

// Check if the player has guessed the entire word
bool Hangman::isWordGuessed() const {
    return guessedWord == word;
}

// Save the high score to the file
void Hangman::saveHighScore(const std::string& playerName) {
    std::ofstream file("highscores.txt", std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error opening high scores file for writing." << std::endl;
        return;
    }

    file << "Word: " << word << " - Player: " << playerName << " - Guesses Left: " << remainingGuesses << std::endl;
    file.close();
}

// Display all high scores stored in the file
void Hangman::displayHighScores() const {
    std::ifstream file("highscores.txt");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the high scores file." << std::endl;
        return;
    }

    std::cout << "High Scores:" << std::endl;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}

// Load high scores from the file
void Hangman::loadHighScores() {
    std::ifstream file("highscores.txt");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the high scores file for reading." << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        highScores.push_back(line);
    }

    file.close();
}

