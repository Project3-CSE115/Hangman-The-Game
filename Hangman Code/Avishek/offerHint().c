#include <stdio.h>
#include <stdbool.h>

#define RESET "\033[0m"
#define BROWN "\033[38;2;139;69;19m"
#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define MAX_THEMES 5
#define MAX_LEVELS 5
#define WORD_COUNT 10

int hintCount, levelCount, themeChoice, wordIndex;
bool hintTaken;

typedef struct {
    char *name;
    char *words[WORD_COUNT];
    char *hints[WORD_COUNT];
} Theme;

typedef struct {
    Theme themes[MAX_THEMES];
} Level;

Level levels[MAX_LEVELS];

void offerHint() {
    char wantHint;

    if (hintCount <= 2) {
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
            printf(YELLOW "\nHint: %s\n\n" RESET,levels[levelCount-1].themes[themeChoice-1].hints[wordIndex]);
            if (hintCount == 3) {
                printf(RED "\nYou have run out of hints\n" RESET);
            }
            Sleep(2000);
        }
        system("cls");
    }
}
