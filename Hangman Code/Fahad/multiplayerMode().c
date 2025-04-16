#include <stdio.h>
#include <stdbool.h>

#define RESET "\033[0m"
#define BROWN "\033[38;2;139;69;19m"
#define RED "\e[0;91m"
#define YELLOW "\033[0;33m"
#define GREEN "\e[0;92m"
#define CYAN "\033[1;36m"
#define PINK "\033[38;2;255;192;203m"
#define PURPLE "\033[1;35m"
#define ROYAL_BLUE "\e[0;94m"
#define LAVENDER "\033[38;5;183m"
#define PASTEL_PINK "\033[38;5;218m"
#define DUSTY_ROSE "\033[38;5;131m"
#define MAX_LENGTH 20
#define MAX_TRIES 6

int correctGuessCount, tries, wins, streak, highestScore, streakBroken;
char guessed[MAX_LENGTH], word[MAX_LENGTH];
bool gameOver, hintTaken, isGuest;

typedef struct {
    char name[MAX_LENGTH];
    int age;
    int streak;
    int highScore;
    int level;
    int game;
    int streakBroken;
    int hintBadge;
    int speedBadge;
    int streakBadge;
} Player;

Player player;

void multiplayerMode() {
    char player1[MAX_LENGTH], player2[MAX_LENGTH], wordToGuess[MAX_LENGTH], hint[MAX_LENGTH], theme[MAX_LENGTH], wantHint, playAgain;
    int player1Score = 0, player2Score = 0;
    int thisPlayer = 1, hintCount = 0;

    printf(PINK "\n<-------MULTIPLAYER MODE------->\n" RESET);
    printf(DUSTY_ROSE "Player 1 and Player 2 will take turns setting the word and guessing.\n" RESET);
    printf(PASTEL_PINK "Each correct guess earns points. The player with the highest score wins!\n" RESET);
    printf(BROWN "\nPress any key to start..." RESET);
    getchar();
    getchar();
    system("cls");

    if (!isGuest) {
        printf(CYAN "Player 1: " RESET);
        printf(PINK "%s\n" RESET, player.name);
        strcpy(player1, player.name);
        printf(CYAN "Enter player 2 name: %s\n" RESET, player2);
    } else {
        printf(CYAN "Enter player 1 name: %s\n" RESET, player1);
        printf(CYAN "Enter player 2 name: %s\n" RESET, player2);
    }

    while (true) {
        memset(guessed, '\0', sizeof(guessed));
        tries = 0;
        correctGuessCount = 0;
        gameOver = false;

        printf(PURPLE "Player %d, enter a word for Player %d to guess: " RESET, thisPlayer, (thisPlayer == 1) ? 2 : 1);
        scanf("%s", wordToGuess);
        printf(PURPLE "Enter the theme of the word: " RESET);
        scanf(" %[^\n]", theme);
        if (hintCount <= 6) {
            printf(PURPLE "Enter a hint for the word: " RESET);
            scanf(" %[^\n]", hint);
        }

        system("cls");

        printf(ROYAL_BLUE "Player %d, it's your turn to guess the word!\n" RESET, (thisPlayer == 1) ? 2 : 1);
        Sleep(2000);
        system("cls");

        while (!gameOver) {
            system("cls");
            displayHintMeter(6, hintCount);
            displayHangman(tries);
            printf(YELLOW "Theme: %s\n\n" RESET, theme);
            if (hintTaken && hintCount <= 6) {
                printf(YELLOW "Hint: %s\n\n" RESET, hint);
            }
            for (int i = 0; i < strlen(wordToGuess); i++) {
                if (wordToGuess[i] == ' ') {
                    printf("  ");
                } else if (guessed[i] != '\0') {
                    printf("%c ", toupper(guessed[i]));
                } else {
                    printf("__ ");
                }
            }

            printf(PURPLE "\n\nGuess a letter: " RESET);
            char guessedLetter;
            scanf(" %c", &guessedLetter);
            while (!isalpha(guessedLetter)) {
                printf(RED "\nInvalid input! Please enter a letter." RESET);
                printf(PURPLE "\n\nGuess a letter: " RESET);
                scanf(" %c", &guessedLetter);
            }

            bool found = false;
            for (int i = 0; i < strlen(wordToGuess); i++) {
                if (toupper(wordToGuess[i]) == toupper(guessedLetter)) {
                    guessed[i] = wordToGuess[i];
                    found = true;
                    correctGuessCount++;
                }
            }

            if (!found) {
                tries++;
                printf(RED "\nThe letter '%c' is not in the word.\n" RESET, guessedLetter);
                Sleep(1000);
                system("cls");
            }

            if (tries == MAX_TRIES) {
                printf(RED "\nGAME OVER! Player %d couldn't guess the word.\n" RESET, (thisPlayer == 1) ? 2 : 1);
                printf(YELLOW "The word was: %s\n" RESET, wordToGuess);
                gameOver = true;
            } else if (correctGuessCount == strlen(wordToGuess)) {
                system("cls");
                displayHangman(tries);
                printf("%s", word);
                printf(GREEN "\nCONGRATULATIONS! Player %d guessed the word.\n" RESET, (thisPlayer == 1) ? 2 : 1);
                gameOver = true;

                if (thisPlayer == 1) {
                    player2Score += (5 * correctGuessCount) - (1 * tries);
                    if (hintTaken) {
                        player2Score -= 3;
                    }
                } else {
                    player1Score += (5 * correctGuessCount) - (1 * tries);
                    if (hintTaken) {
                        player1Score -= 3;
                    }
                }
            }
            if (tries == 3 && !gameOver && hintCount <= 6) {
                system("cls");
                printf(BROWN "\n\nWould you like a hint?(y/n): " RESET);
                scanf(" %c", &wantHint);
                while (tolower(wantHint) != 'y' && tolower(wantHint) != 'n') {
                    printf(RED "\n\nInvalid input. Enter 'y' or 'n'.\n" RESET);
                    printf(BROWN "\n\nWould you like a hint?(y/n): " RESET);
                    scanf(" %c", &wantHint);
                }
                system("cls");
                if (tolower(wantHint) == 'y') {
                    hintTaken = true;
                    hintCount++;
                    printf(YELLOW "\nHint: %s\n\n" RESET, hint);
                    Sleep(1000);
                    system("cls");
                }
            }
        }

        thisPlayer = (thisPlayer == 1) ? 2 : 1;

        printf(PURPLE "\nDo you want to play another round? (y/n): " RESET);
        scanf(" %c", &playAgain);
        while (tolower(playAgain) != 'y' && tolower(playAgain) != 'n') {
            printf(RED "\nInvalid input. Enter 'y' or 'n'.\n" RESET);
            printf(PURPLE "\nDo you want to play another round? (y/n): " RESET);
            scanf(" %c", &playAgain);
        }
        if (tolower(playAgain) == 'n') {
            break;
        }
        system("cls");
    }
    system("cls");
    printf(LAVENDER "\n<-------FINAL SCORES------->\n" RESET);
    printf(PINK "%s: %d points\n" RESET, player1, player1Score);
    printf(PINK "%s: %d points\n" RESET, player2, player2Score);

    if (player1Score > player2Score) {
        printf(GREEN "\n%s wins!\n" RESET, player1);
        wins++;
        if (player1Score > player.highScore) {
            player.highScore = player1Score;
            saveProgress();
        }
        if (wins > player.streak) {
            player.streak = wins;
            saveProgress();
        }
        player.streakBroken = 0;
        Sleep(2000);
        winAnimation();
    } else if (player2Score > player1Score) {
        printf(GREEN "\n%s wins!\n" RESET, player2);
        player.streakBroken = 1;
        Sleep(2000);
        winAnimation();
    } else {
        printf(YELLOW "\nIt's a tie!\n" RESET);
    }

    printf(BROWN "\nPress any key to return to the Game Menu..." RESET);
    getchar();
    getchar();
    system("cls");
    gameMenu();
}