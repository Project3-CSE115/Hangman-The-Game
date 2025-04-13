#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
#define SLEEP(ms) Sleep(ms)
#else
#define SLEEP(ms) usleep((ms) * 1000)
#endif

#define DELAY 60
#define RESET "\033[0m"
#define BLINK "\033[5m"
#define BOLD "\033[1m"

#define GREEN "\033[0;32m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[0;33m"
#define BOLD_YELLOW "\033[1;33m"
#define RED "\033[0;31m"
#define ORANGE "\033[38;2;255;140;0m"
#define LAVENDER "\033[38;5;183m"
#define BROWN "\033[38;2;139;69;19m"
#define PINK "\033[38;2;255;192;203m"
#define DARK_PINK "\033[38;2;231;84;128m"
#define PURPLE "\033[1;35m"
#define ROYAL_BLUE "\033[0;34m"
#define CREAM "\033[38;2;255;253;208m"
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

#define PASTEL_PINK      "\033[38;5;218m"
#define PASTEL_PEACH     "\033[38;5;219m"
#define PASTEL_LAVENDER  "\033[38;5;219m"
#define PASTEL_BLUE      "\033[38;5;153m"
#define PASTEL_MINT      "\033[38;5;120m"
#define PASTEL_LIME      "\033[38;5;190m"
#define PASTEL_TURQUOISE "\033[38;5;87m"
#define PASTEL_YELLOW    "\033[38;5;227m"
#define PASTEL_ORANGE    "\033[38;5;214m"
#define PASTEL_PURPLE    "\033[38;5;183m"
#define PASTEL_SALMON    "\033[38;5;209m"

#define TERRACOTTA      "\033[38;5;173m"
#define OLIVE_GREEN     "\033[38;5;100m"
#define SAND_BEIGE      "\033[38;5;180m"
#define FOREST_GREEN    "\033[32m"
#define CLAY_BROWN      "\033[38;5;137m"
#define KHAKI           "\033[38;5;228m"
#define RUSTIC_ORANGE   "\033[38;5;166m"
#define DEEP_MOSS       "\033[38;5;58m"
#define DUSTY_ROSE      "\033[38;5;131m"
#define BURNT_UMBER     "\033[38;5;94m"
#define BARK_BROWN      "\033[38;5;52m"


void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

typedef struct Player
{
    char username[50];
    int DOB[20];
    char current_Status[30];
    char fav_Category[30];
    char last_Played[20];
} Player;

void typeEffect(const char *text, const char *color)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%s%c" RESET, color, text[i]);
        fflush(stdout);
        Sleep(50);
    }
    printf("\n");
}

void typeEffect_Beep(const char *text, const char *color)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%s%c" RESET, color, text[i]);
        fflush(stdout);
        Beep(700 + (i * 20), 250);
        Sleep(250);
    }
    printf("\n");
}

void loadingDots(int count, int delay, const char *color)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s." RESET, color);
        fflush(stdout);
        Sleep(delay);
    }
    printf("\n");
}

void waveText(const char *text, const char *color1, const char *color2)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (i % 2 == 0)
            printf("%s%c" RESET, color1, text[i]);
        else
            printf("%s%c" RESET, color2, text[i]);
        fflush(stdout);
        Sleep(50);
    }
    printf("\n");
}

void Main_Menu(Player *player)
{
    int choice;
    do
    {
        clearScreen();

        printf(BLINK PASTEL_PURPLE "~~~~~~~ MAIN MENU ~~~~~~~\n" RESET);

        printf(PASTEL_PINK      "1. Start New Game\n" RESET);
        printf(PASTEL_SALMON    "2. Resume Game\n" RESET);
        printf(PASTEL_LAVENDER  "3. View Profile\n" RESET);
        printf(PASTEL_YELLOW    "4. View Progress\n" RESET);
        printf(PASTEL_BLUE      "5. View Instructions\n" RESET);
        printf(PASTEL_MINT      "6. Credits\n" RESET);
        printf(PASTEL_LIME      "7. Sign Out\n" RESET);

        printf(PASTEL_TURQUOISE "Enter Your Choice: " RESET);

        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid input. Please enter a number from 1-7.\n" RESET);
            while (getchar() != '\n');
            Sleep(1000);
             clearScreen();
             continue;
        }
        if (choice < 1 || choice > 7)
        {
            printf(RED "Invalid number. Please enter a number from 1-7.\n" RESET);
            Sleep(1000);
             clearScreen();

            continue;
        }
        Sleep(1000);
         clearScreen();


        switch (choice)
        {
        case 1:
            printf("game-logic");
            Sleep(2000);
            clearScreen();
            break;
        case 2:
            printf("Resume");
            Sleep(2000);
            clearScreen();
            break;
        case 3:
            printf("Profile details");
            Sleep(2000);
            clearScreen();
            break;
        case 4:
            printf("Player Progress");
            Sleep(2000);
            clearScreen();
            break;
        case 5:
            typeEffect("Welcome to the HANGMAN game!\n", TERRACOTTA);
            typeEffect("Your task is to guess the word before the stickman is fully hanged.", OLIVE_GREEN);
            typeEffect("There are five difficulty stages and five levels for each stage.", SAND_BEIGE);
            typeEffect("You can choose the theme for each stages.", FOREST_GREEN);
            typeEffect("You'll get an option for hint after 3 incorrect guesses in each level.", CLAY_BROWN);
            typeEffect("However...You only have 10 hints throughout the game-play.", KHAKI);
            typeEffect("Good news!You'll earn a bonus hint for guessing 3 words in a row.", RUSTIC_ORANGE);
            typeEffect("+5 points will be added for each correct guess.", DEEP_MOSS);
            typeEffect("3 points will be deducted for using a hint.", DUSTY_ROSE);
            typeEffect("1 points will be deducted for each incorrect guess.", BURNT_UMBER);
            typeEffect("Maximum wrong guesses: 6", BARK_BROWN);
            typeEffect("Good Luck!",HBLK);
            Sleep(2000);

            break;
        case 6:
            typeEffect_Beep("~~~~~~~CREDITS~~~~~~~", YELLOW);
            waveText("1. Priyonti Tabassum Haque", ROYAL_BLUE, PURPLE);
            waveText("2. Sumaiya Yasmin Nairit", RED, ORANGE);
            waveText("3. Dizzya Al Fahad", HBLU, HWHT);
            waveText("4. Avishek Saha", BOLD_YELLOW, GREEN);
            Sleep(2000);
            break;
        case 7:
            typeEffect("Signing out", RED);
            loadingDots(3, 1000, RED);
            break;
        }

        if (choice == 5 || choice == 6)
        {
            printf(HBLK "\nPress Enter to return to the main menu..." RESET);
            getchar();
            getchar();
        }

    } while (choice != 7);
}


