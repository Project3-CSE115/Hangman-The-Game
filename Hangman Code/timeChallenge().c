#include <stdio.h>
#include <stdbool.h>

#define RESET "\033[0m"
#define BROWN "\033[38;2;139;69;19m"
#define YELLOW "\033[0;33m"
#define PINK "\033[38;2;255;192;203m"

int remainingTime;
bool timeChallenge;

void timeChallengeMode() {
    remainingTime = 60;
    timeChallenge = true;

    printf(YELLOW "\n<-------TIME CHALLENGE MODE------->\n" RESET);
    printf(PINK "You have 1 minute to guess the word for each game.\n" RESET);
    printf(PINK "Try to guess the word before time runs out!\n" RESET);
    printf(BROWN "\nPress any key to start..." RESET);

    while (getchar() != '\n');

    getchar();
    system("cls");
}