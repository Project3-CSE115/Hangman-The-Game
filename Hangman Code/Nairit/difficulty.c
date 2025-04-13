#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESET "\033[0m"
#define RED "\033[0;31m"


#define MAX_WORDS 500
#define MAX_LEVELS 10
#define WORD_COUNT 10
#define MAX_THEMES 5
#define MAX_LENGTH 20


void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void select_Difficulty()
{
    int level;
    while (1)
    {
        printf("Select a difficulty level:\n");
        printf("1. Easy\n");
        printf("2. Normal\n");
        printf("3. Medium\n");
        printf("4. Hard\n");
        printf("5. Expert\n");
        printf("Enter Your Choice:");

        if (scanf("%d", &level) != 1 || level < 1 || level > 5)
        {
            printf(RED "Invalid input. Try Again.\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
            clearScreen();
            continue;
        }
        else
        {
            break;
        }
    }

    clearScreen();
    select_Category(level - 1);

}

void select_Category(int level)
{
    int category;

    printf("Select a category for level %d:\n", level + 1);

    for (int i = 0; i < MAX_THEMES; i++)
    {
        printf("%d. %s\n", i + 1, levels[level].themes[i].name);
    }

    while (1)
    {
        printf("Enter Your Choice:");
        if (scanf("%d", &category) != 1 || category < 1 || category > MAX_THEMES)
        {
            printf(RED "Invalid input.Try Again\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
            clearScreen();
            continue;
        }
        else
        {
            break;

        }

    }

    int wordIndex;
    char* word = fetch_Word(level, category - 1, &wordIndex);
    char* hint = levels[level].themes[category - 1].hints[wordIndex];

                 clearScreen();
    play_Game(word, hint, level);

}



char* fetch_Word(int level, int category, int *index)
{
    srand(time(0));
    int wordIndex = rand() % WORD_COUNT;
    *index = wordIndex;
    return levels[level].themes[category].words[wordIndex];
}



void play_Game(char *word, char *hint, int level);


