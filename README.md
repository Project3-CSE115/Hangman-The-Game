# Hangman Game In C
A simple, interactive console-based Hangman game implemented in C for the command-line. This project is designed as a learning exercise in C programming, focusing on basic game logic, user input handling, and ASCII art-based representation, along with some visual and sound elements.

Table of Contents
1. Features
2. Installation
3. Usage
4. Code Overview
5. Challenges and Future Enhancements
   
Features
Random Word Selection: Chooses a random word from a predefined list for each game session. Word lists are divided for each theme and each level. Words progress in difficulty per level as well as per game each level.

Interactive Gameplay: Accepts player guesses, updating the game state based on correct and incorrect inputs. Allows pla

ASCII Art Visuals: Displays progressive hangman states as wrong guesses increase.

Win/Loss Detection: Tracks correct guesses and ends the game when the word is fully guessed or maximum incorrect attempts are reached.

Installation
1. Clone the Repository
2. Compile the Code: Use a C compiler (e.g. GCC) to compile the program:
3. Run the Program

Usage
When you run the program, you'll see the title and a welcome message along with game instructions. The program randomly selects a word, and you will be prompted to enter letter guesses. The current state of the word and the hangman (via ASCII art) are displayed after each guess. The game ends when either:

The entire word is correctly guessed (win), or
The maximum number of incorrect guesses (6) is reached (loss).

Code Overview

displayHangman(int attempts): Displays the ASCII art corresponding to the number of incorrect attempts.

displaytitle(): Prints the game title and decorative header.

displayWord(const char *word, const int *guessed): Prints the current progress of the word with correctly guessed letters and underscores for missing ones.

main(): Sets up the game environment (random word selection, initialization of game state).
Contains the main game loop which processes user input and updates the game state.
Determines and displays the final outcome (win or loss).

Challenges and Future Enhancements
Challenges: Handling files for player statistics and history for save/load feature.
Integrating and synchronizing ASCII art visuals with game logic.

Future Enhancements: 
Expand the word list for more diverse gameplay.
