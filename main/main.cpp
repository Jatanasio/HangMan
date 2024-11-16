#include <iostream>
#include <vector>
#include "hangman.h"
#include <fstream>
#include <ctime>

// Function to load words from a file
std::vector<std::string> loadWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            words.push_back(word);
        }
        file.close();
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    return words;
}

// Function to display the hangman based on the number of wrong guesses
void displayHangman(int wrongGuesses) {
    const std::string hangmanStages[] = {
        "      +---+\n"
        "          |\n"
        "          |\n"
        "          |\n"
        "          |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "          |\n"
        "          |\n"
        "          |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "      O   |\n"
        "          |\n"
        "          |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "      O   |\n"
        "      |   |\n"
        "          |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "      O   |\n"
        "     /|   |\n"
        "          |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "      O   |\n"
        "     /|\\  |\n"
        "          |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "      O   |\n"
        "     /|\\  |\n"
        "     /    |\n"
        "          |\n"
        "        =======",

        "      +---+\n"
        "      |   |\n"
        "      O   |\n"
        "     /|\\  |\n"
        "     / \\  |\n"
        "          |\n"
        "        ======="
    };

    // Display the hangman based on the wrong guesses
    std::cout << hangmanStages[wrongGuesses] << std::endl;
}

// Function to display the main menu
void displayMainMenu() {
    std::cout << "\n===============================================" << std::endl;
    std::cout << "           WELCOME TO HANGMAN GAME           " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "1. View High Scores" << std::endl;
    std::cout << "2. Play Hangman" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

int main() {
    // Load words from the file
    std::vector<std::string> words = loadWordsFromFile("words.txt");

    int choice;
    std::string playerName;

    while (true) {
        displayMainMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;

        std::cout << std::endl;

        if (choice == 1) {
            // View High Scores
            std::cout << "Enter the word to view high scores: ";
            std::string word;
            std::cin >> word;
            Hangman game(word, 6);
            game.displayHighScores();
        } 
        else if (choice == 2) {
            // Play Hangman
            std::cout << "Enter your name: ";
            std::cin >> playerName;

            std::srand(std::time(nullptr));
            std::string randomWord = words[std::rand() % words.size()];
            Hangman game(randomWord, 6);

            int wrongGuesses = 0;

            while (!game.isGameOver()) {
                game.displayState();
                displayHangman(wrongGuesses);  // Display hangman

                std::cout << "\nEnter a letter: ";
                char letter;
                std::cin >> letter;

                if (!game.guessLetter(letter)) {
                    wrongGuesses++;  // Increment wrong guesses on incorrect guess
                }
            }

            if (game.isWordGuessed()) {
                std::cout << "\nYou guessed the word!" << std::endl;
            } else {
                std::cout << "\nGame over. You ran out of guesses!" << std::endl;
            }

            // Save the high score
            game.saveHighScore(playerName);
        }
        else if (choice == 3) {
            // Exit
            break;
        } else {
            std::cout << "Invalid option. Try again." << std::endl;
        }

        std::cout << std::endl; // Extra whitespace for readability
    }

    return 0;
}
