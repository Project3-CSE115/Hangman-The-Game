#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define MAX_TRIES 6
#define MAX_WORDS 250
#define MAX_LEVELS 5
#define WORD_COUNT 10
#define MAX_THEMES 5
#define MAX_LENGTH 21
#define MAX_GAMES 3
#define MAX_BADGES 10
#define BLINK "\033[5m"
#define CLEAR "cls"
#define SLEEP(ms) Sleep(ms)
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define GRAY "\x1B[90m"
#define WHITE "\x1B[97m"
#define GREEN "\e[0;92m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define YELLOW "\033[1;33m"
#define RED "\e[0;91m"
#define ORANGE "\033[38;5;214m"
#define LAVENDER "\033[38;5;183m"
#define BROWN "\033[38;2;139;69;19m"
#define PINK "\033[38;2;255;192;203m"
#define DARK_PINK "\033[38;2;231;84;128m"
#define PURPLE "\033[1;35m"
#define ROYAL_BLUE "\e[0;94m"
#define CREAM "\033[38;2;255;253;208m"
#define HBLK "\e[0;90m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"
#define PASTEL_PINK "\033[38;5;218m"
#define PASTEL_PEACH "\033[38;5;219m"
#define PASTEL_LAVENDER "\033[38;5;219m"
#define PASTEL_BLUE "\033[38;5;153m"
#define PASTEL_MINT "\033[38;5;120m"
#define PASTEL_LIME "\033[38;5;190m"
#define PASTEL_TURQUOISE "\033[38;5;87m"
#define PASTEL_YELLOW "\033[38;5;227m"
#define PASTEL_ORANGE "\033[38;5;214m"
#define PASTEL_PURPLE "\033[38;5;183m"
#define PASTEL_SALMON "\033[38;5;209m"
#define TERRACOTTA "\033[38;5;173m"
#define OLIVE_GREEN "\033[38;5;100m"
#define SAND_BEIGE "\033[38;5;180m"
#define FOREST_GREEN "\033[32m"
#define CLAY_BROWN "\033[38;5;137m"
#define KHAKI "\033[38;5;228m"
#define RUSTIC_ORANGE "\033[38;5;166m"
#define DEEP_MOSS "\033[38;5;58m"
#define DUSTY_ROSE "\033[38;5;131m"
#define BURNT_UMBER "\033[38;5;94m"
#define BARK_BROWN "\033[38;5;52m"

int remainingTime, tries = 0, correctGuessCount = 0, themeChoice, wordIndex, hintCount = 0, wins = 0, score = 0;
bool hintTaken, gameOver, isGuest = false, timeChallenge = false, revealLetter = false;
const char *word;
char guessedLetter, guessed[MAX_LENGTH];
time_t startTime, currentTime;
void gameMenu();
void gameModeMenu();
void offerHint();
void calculateScore();
void awardBadge(int badgeIndex);
void saveProgress();
void displayHangman(int tries);

typedef struct {
    char *name;
    char *words[WORD_COUNT];
    char *hints[WORD_COUNT];
} Theme;

typedef struct {
    Theme themes[MAX_THEMES];
} Level;

Level levels[MAX_LEVELS];
int levelCount = 0;

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
    int timeBadge;
} Player;

Player player;

const char *badges[MAX_BADGES] = {"Rookie Rambler","Casual Challenger","Puzzle Pro","Mind Master",
    "Hangman Hero","Hintless Hero","Speed Guesser","Streak Master","Time Warrior","Ultimate Champion"};

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

void addLevel(const char *themeList[MAX_THEMES], const char *wordLists[MAX_THEMES][WORD_COUNT], const char *hintLists[MAX_THEMES][WORD_COUNT]) {
    if (levelCount >= MAX_LEVELS) {
        printf("\nLevel limit reached.\n");
        return;
    }

    for (int i = 0; i < MAX_THEMES; i++) {
        levels[levelCount].themes[i].name = strdup(themeList[i]);
        if (levels[levelCount].themes[i].name == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        for (int j = 0; j < WORD_COUNT; j++) {
            levels[levelCount].themes[i].words[j] = strdup(wordLists[i][j]);
            levels[levelCount].themes[i].hints[j] = strdup(hintLists[i][j]);

            if (levels[levelCount].themes[i].words[j] == NULL || levels[levelCount].themes[i].hints[j] == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
        }
    }

    levelCount++;
}

bool nameTaken(char playerName[MAX_LENGTH]) {
    char name[MAX_LENGTH];
    int age;

    FILE *file = fopen("players.txt","r");
    if (file == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return false;
    }
    while (fscanf(file, "%s %d", name, &age) != EOF) {
        if (strcmp(playerName,name) == 0) {
            return true;
        }
    }
    fclose(file);
    return false;
}

bool nameValid(char playerName[MAX_LENGTH]) {
    
    if (strlen(playerName) > 20) {
        return false;
    } else {
        return true;
    }
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isDobValid(const char *dob) {
    int day, month, year;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (strlen(dob) != 10 || dob[2] != '/' || dob[5] != '/') {
        return false;
    }

    day = atoi(&dob[0]);
    month = atoi(&dob[3]);
    year = atoi(&dob[6]);

    if (year < 1900 || year > 2025) {
        return false;
    }

    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    int currentYear = currentDate.tm_year + 1900;
    int currentMonth = currentDate.tm_mon + 1;
    int currentDay = currentDate.tm_mday;

    player.age = currentYear - year;
    if (currentMonth < month || (currentMonth == month && currentDay < day)) {
        player.age--;
    }

    return true;
}

void animateText(const char *text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        Sleep(delay);
    }
}

void winAnimation() {

    FILE *f = fopen("C:\\Users\\HP\\Downloads\\MyCode\\victory-fanfare.wav", "r");
    if (f) {
        fclose(f);
        PlaySound(TEXT("C:\\Users\\HP\\Downloads\\MyCode\\victory-fanfare.wav"), NULL, SND_FILENAME | SND_ASYNC);
    } else {
        printf(RED "Victory sound file not found!\n" RESET);
    }

    const char *trophy[] = {
        YELLOW "   ____   " RESET,
        YELLOW "  /    \\  " RESET,
        YELLOW " /______\\ " RESET,
        YELLOW "   ||||   " RESET,
        YELLOW "   ||||   " RESET
    };


    for (int i = 0; i < 5; i++) {
        system("cls");
        for (int j = 0; j <= i; j++) {
            printf("%s\n", trophy[j]);
        }
        Sleep(200);
    }

    const char *fireworks[] = {
        "    *    ",
        "  *   *  ",
        "*  * *  *",
        " * * * * ",
        "*  * *  *",
        "  *   *  "
    };

    const char *colors[] = { YELLOW, CYAN, MAGENTA, GREEN };


    for (int i = 0; i < 8; i++) {
        system("cls");
        printf(YELLOW);
        for (int j = 0; j < 5; j++) {
            printf("%s\n", trophy[j]);
        }
        printf(colors[i % 4]);
        for (int j = 0; j < 6; j++) {
            printf("%s\n", fireworks[(j + i) % 6]);
        }
        Sleep(150);
    }

    printf(GREEN);
    animateText("\nYou Won! Victory!\n", 40);
    printf(RESET);
}

void printHangman(int blink) {
    printf(BLINK RED"     --------\n" RESET);
    printf(BLINK RED"     |      |\n" RESET);
    printf(BLINK RED"     |      O\n" RESET);
    printf(BLINK RED"     |     /|\\\n" RESET);
    printf(BLINK RED"     |     / \\\n" RESET);
    printf(BLINK RED"     |\n" RESET);
    printf(BLINK RED"  ___|___\n" RESET);

    if (blink)
        printf("     X_X   GAME OVER\n");
    else
        printf("     -_-   GAME OVER\n");
}

void loseAnimation() {
    printHangman(6);
    Sleep(500);

    const char *cloud_frames[][4] = {
        {
            GRAY "   ~~   " RESET,
            WHITE " ~~~~~~ " RESET,
            WHITE "~  ~~  ~" RESET,
            GRAY " ~~  ~~ " RESET
        },
        {
            GRAY "  ~~~   " RESET,
            WHITE " ~~~~~~~" RESET,
            WHITE "~~ ~~ ~~" RESET,
            GRAY " ~~~~  " RESET
        },
        {
            GRAY " ~~ ~~  " RESET,
            WHITE "~~~~~~~~" RESET,
            WHITE "~ ~~ ~~~" RESET,
            GRAY " ~~~   " RESET
        }
    };
    int num_frames = 3;
    int cloud_rows = 4;
    int max_steps = 8;

    for (int step = 0; step < max_steps; step++) {
        system("cls");
        printHangman(6);
        int frame = (step % num_frames);
        int indent = step;
        for (int i = 0; i < cloud_rows; i++) {
            for (int j = 0; j < indent; j++) {
                printf(" ");
            }
            printf("%s  ", cloud_frames[frame][i]);
            for (int j = 0; j < 5; j++) {
                printf(" ");
            }
            printf("%s\n", cloud_frames[(frame + 1) % num_frames][i]);
        }
        Sleep(250);
    }

    const char *flash[] = {
        YELLOW "   *ZAP*   " RESET,
        YELLOW "  *CRACK*  " RESET,
        YELLOW "   *BZZT*  " RESET
    };
    for (int i = 0; i < 3; i++) {
        system("cls");
        printHangman(6);
        for (int j = 0; j < cloud_rows; j++) {
            printf("%s  %s\n", cloud_frames[0][j], cloud_frames[1][j]);
        }
        printf("\n%s\n", flash[i % 3]);
        Sleep(150);
        system("cls");
        printHangman(6);
        for (int j = 0; j < cloud_rows; j++) {
            printf("%s  %s\n", cloud_frames[0][j], cloud_frames[1][j]);
        }
        Sleep(100);
    }

    FILE *f = fopen("C:\\Users\\HP\\Downloads\\MyCode\\lightning.wav", "r");
    if (f) {
        fclose(f);
        PlaySound(TEXT("C:\\Users\\HP\\Downloads\\MyCode\\lightning.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }

    const char *bolt[] = {
        YELLOW "      \\\\    " RESET,
        YELLOW "      //   " RESET,
        YELLOW "     //    " RESET,
        YELLOW "     \\\\     " RESET,
        YELLOW "      \\\\    " RESET,
        YELLOW "      \\\\    " RESET,
        YELLOW "      //    " RESET,
        YELLOW "     //     " RESET,
        YELLOW "    \\\\      " RESET,
        YELLOW "    ||      " RESET,
    };
    for (int i = 0; i < 3; i++) {
        system("cls");
        for (int j = 0; j < cloud_rows; j++) {
            printf("%s  %s\n", cloud_frames[0][j], cloud_frames[1][j]);
        }
        printf("\n");
        for (int j = 0; j < 10; j++) {
            printf("    ");
            printf("%s\n", bolt[j]);
        }
        Sleep(200);
        system("cls");
        for (int j = 0; j < cloud_rows; j++) {
            printf("%s  %s\n", cloud_frames[0][j], cloud_frames[1][j]);
        }
        Sleep(100);
    }

    system(CLEAR);
    for (int j = 0; j < cloud_rows; j++) {
        printf("%s  %s\n", cloud_frames[0][j], cloud_frames[1][j]);
    }
    printf("\n");
    for (int j = 0; j < 10; j++) {
        printf("    ");
        printf("%s\n", bolt[j]);
    }
    printf("         _.,,,.._\n");
    printf("      ,d$$$$$$$SSIi:.\n");
    printf("    ,S$$$$$$$$$$$$SIIi:.\n");
    printf("   jI$$$$$$$$$$$$$SISSi:.\n");
    printf("  ,S$$$$$$$$$$$$$$$$$$Ii:.\n");
    printf(" j*?$$$$$$$$$$$$$$$$$$Ii\n");
    printf(" :  ?$$$$$$$$$$$S7IISS$$I:\n");
    printf("j_ /$$7'*4$$$$7:iIS$$$$$I'\n");
    printf("*?''?$$:  '$k :iIIS$$$$7'\n");
    printf("||   ?$L,  ,d$    $$$$7'\n");
    printf(",d._J$$$$S$$$L,_*'$$$\n");
    printf("?$$$$$$k:?$$**,  *''\n");
    printf("\\:`****^`:jIS7\n");
    printf("j$k,i;/_,oSSI'\n");
    printf("?SSS$$$$$?*`\n");
    printf(" `****''`\n");
    printf(RED);
    animateText("\nStruck Out! Game Over.\n", 40);
    f = fopen("C:\\Users\\HP\\Downloads\\MyCode\\game-over.wav", "r");
    if (f) {
        fclose(f);
        PlaySound(TEXT("C:\\Users\\HP\\Downloads\\MyCode\\game-over.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }
    printf(RESET);
}

void displayHintMeter(int maxHints, int usedHints) {
    printf(ORANGE "Hint Meter: " RESET);
    for (int i = 0; i < maxHints; i++) {
        if (i < usedHints) {
            printf(ORANGE "█" RESET);
        } else {
            printf(ORANGE "░" RESET);
        }
    }
    printf("\n");
}

void createAccount() {
    char playerName[MAX_LENGTH], dob[11];

    printf(PURPLE "\nEnter player name: " RESET);
    scanf("%s", playerName);
    while (nameTaken(playerName) || !nameValid(playerName)) {
        if (nameTaken(playerName)) {
            printf(RED "\nThis player name is already taken.\n" RESET);
        } else {
            printf(RED "\nThe player name should be less than 20 characters.\n" RESET);
        }
        printf(PURPLE "\nEnter player name: " RESET);
        scanf("%s", playerName);
    }
    printf(PURPLE "\nEnter date of birth(DD/MM/YYYY): " RESET);
    scanf("%s", dob);
    while (!isDobValid(dob)) {
        printf(RED "\nInalid dob format.\n" RESET);
        printf(PURPLE "\nEnter date of birth(DD/MM/YYYY): " RESET);
        scanf("%s", dob);
    }
    strcpy(player.name, playerName);
    player.streak = 0;
    player.highScore = 0;
    player.level = 1;
    player.game = 1;
    player.streakBroken = 0;
    player.hintBadge = 0;
    player.speedBadge = 0;
    player.streakBadge = 0;
    player.timeBadge = 0;
    FILE *file1 = fopen("players.txt","a");
    if (file1 == NULL) {
        printf(RED "\nError opening this file!\n" RESET);
        return;
    }
    fprintf(file1, "%s %d\n", player.name, player.age);
    fclose(file1);
    FILE *file2 = fopen("stats.txt","a");
    if (file2 == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }
    fprintf(file2, "%s %d %d %d %d %d %d %d %d %d\n", player.name, player.streak, player.highScore, player.level, player.game, player.streakBroken, player.hintBadge, player.speedBadge, player.streakBadge, player.timeBadge);
    fclose(file2);
    printf(GREEN "\nAccount Created Successfully!\n" RESET);
}

void playerMenu() {
    int choice, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, tempB4, age;
    bool playerFound = false;
    char playerName[MAX_LENGTH], tempName[MAX_LENGTH], redirect;

    system("cls");
    printf(CYAN BOLD "\nWelcome to HANGMAN\n" RESET);
    printf(CREAM "\n1. Create Account\n" RESET);
    printf(CREAM "2. Log In\n" RESET);
    printf(CREAM "3. Play As Guest\n" RESET);
    printf(PURPLE "\nEnter a choice: " RESET);
    while (scanf("%d", &choice) != 1) {
        printf(RED "\nInvalid input! Please enter a number.\n" RESET);
        printf(PURPLE "\nEnter a choice: " RESET);
        while (getchar() != '\n');
        continue;
    }
    system("cls");
    switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            do {
                printf(PURPLE "\nEnter player name: " RESET);
                scanf("%s", playerName);
                while (!nameValid(playerName)) {
                    printf(RED "\nThe player name should be less than 20 characters.\n" RESET);
                    printf(PURPLE "\nEnter player name: " RESET);
                    scanf("%s", playerName);
                }

                FILE *file = fopen("players.txt","r");
                if (file == NULL) {
                    printf(RED "\nError opening file!\n" RESET);
                    return;
                }
                while (fscanf(file, "%s %d", tempName, &age) != EOF) {
                    if (strcmp(playerName, tempName) == 0) {
                        printf(GREEN "\nLog In Successful!\n" RESET);
                        FILE *file1 = fopen("stats.txt","r");
                        if (file1 == NULL) {
                            printf(RED "\nError opening file!\n" RESET);
                            return;
                        }
                        while (fscanf(file1, "%s %d %d %d %d %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken, &tempB1, &tempB2, &tempB3, &tempB4) != EOF) {
                            if (strcmp(tempName, playerName) == 0) {
                                strcpy(player.name, playerName);
                                player.streak = tempStreak;
                                player.highScore = tempScore;
                                player.level = tempLevel;
                                player.game = tempGame;
                                player.streakBroken = tempBroken;
                                if (player.streakBroken == 0) {
                                    wins = player.streak;
                                }
                                player.hintBadge = tempB1;
                                player.speedBadge = tempB2;
                                player.streakBadge = tempB3;
                                player.timeBadge = tempB4;
                                break;
                            }
                        }
                        fclose(file1);
                        player.age = age;
                        playerFound = true;
                        fclose(file);
                        return;
                    } 
                }
                if (!playerFound) {
                    printf(BROWN "\nYou don't have an account.\n" RESET);
                    printf(PURPLE "\nWant to create account?(y/n): " RESET);
                    scanf(" %c", &redirect);
                    while (tolower(redirect) != 'y' && tolower(redirect) != 'n') {
                        printf(RED "\nInvalid input. Enter 'y' or 'n'.\n" RESET);
                        printf(PURPLE "\nWant to create account?(y/n): " RESET);
                        scanf(" %c", &redirect);
                    }
                    if (tolower(redirect) == 'y') {
                        createAccount();
                    }
                }
            } while (tolower(redirect) == 'n');
            break;
        case 3:
            isGuest = true;
            return;
        default:
            printf(RED "\nInvalid choice. Enter one of the options on screen.\n" RESET);
    }
}

void playerDetails() {
    int tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, tempB4, age;
    char edit, newPlayerName[MAX_LENGTH], tempName[MAX_LENGTH];

    while (1) {
        printf(ROYAL_BLUE "\nPlayer Name: " RESET);
        printf("%s\n", player.name);
        printf(ORANGE "\nLongest Streak: " RESET);
        printf("%d\n", player.streak);
        printf(YELLOW "\nHighest Score: " RESET);
        printf("%d\n", player.highScore);
        printf(PINK "\nCurrent Level: " RESET);
        printf("%d\n", player.level);
        printf(GREEN "\nBadges Earned: \n" RESET);
        if (player.level >= 2) printf("%s\n", badges[0]);
        if (player.level >= 3) printf("%s\n", badges[1]);
        if (player.level >= 4) printf("%s\n", badges[2]);
        if (player.level >= 5) printf("%s\n", badges[3]);
        if (player.level >= 6) printf("%s\n", badges[4]);
        if (player.level == 6) printf("%s\n", badges[9]);
        if (player.hintBadge == 1) printf("%s\n", badges[5]);
        if (player.speedBadge == 1) printf("%s\n", badges[6]);
        if (player.streakBadge == 1) printf("%s\n", badges[7]);
        if (player.timeBadge == 1) printf("%s\n", badges[8]);
        printf(PURPLE "\nWant to edit player name?(y/n): " RESET);
        scanf(" %c", &edit);
        while (tolower(edit) != 'y' && tolower(edit) != 'n') {
            printf(RED "\nInvalid input. Enter 'y' or 'n'.\n" RESET);
            printf(PURPLE "\nWant to edit player name?(y/n): " RESET);
            scanf(" %c", &edit);
        }
        if (tolower(edit) == 'y') {
            system("cls");
            printf(PURPLE "\nEnter new player name: " RESET);
            scanf("%s", newPlayerName);
            while (nameTaken(newPlayerName) || !nameValid(newPlayerName)) {
                if (nameTaken(newPlayerName)) {
                    printf(RED "\nThis player name is already taken.\n" RESET);
                } else {
                    printf(RED "\nThe player name should be less than 20 characters.\n" RESET);
                }
                printf(PURPLE "\nEnter new player name: " RESET);
                scanf("%s", newPlayerName);
            }
            FILE *file = fopen("players.txt","r");
            FILE *tempFile = fopen("temp.txt","w");
            if (file == NULL || tempFile == NULL) {
                printf(RED "\nError opening file!\n" RESET);
                return;
            }
            while (fscanf(file, "%s %d", tempName, &age) != EOF) {
                if (strcmp(tempName, player.name) == 0) {
                    fprintf(tempFile, "%s %d\n", newPlayerName, age);
                } else {
                    fprintf(tempFile, "%s %d\n", tempName, age);
                }
            }
            fclose(file);
            fclose(tempFile);
            if (remove("players.txt") != 0) {
                printf(RED "\nError deleting players.txt!\n" RESET);
            }
            if (rename("temp.txt", "players.txt") != 0) {
                printf(RED "\nError renaming temp.txt to players.txt!\n" RESET);
            }

            FILE *file2 = fopen("stats.txt","r");
            FILE *tempFile2 = fopen("temp.txt","w");
            if (file2 == NULL || tempFile2 == NULL) {
                printf(RED "\nError opening file!\n" RESET);
                return;
            }
            while (fscanf(file2, "%s %d %d %d %d %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken, &tempB1, &tempB2, &tempB3, &tempB4) != EOF) {
                if (strcmp(tempName, player.name) == 0) {
                    fprintf(tempFile2, "%s %d %d %d %d %d %d %d %d %d\n", newPlayerName, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, tempB4);
                } else {
                    fprintf(tempFile2, "%s %d %d %d %d %d %d %d %d %d\n", tempName, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, tempB4);
                }
            }
            fclose(file2);
            fclose(tempFile2);
            remove("stats.txt");
            rename("temp.txt","stats.txt");
            strcpy(player.name, newPlayerName);
            printf(GREEN "\nPlayer Name Updated Successfully!\n" RESET);
            Sleep(1000);
            system("cls");
        } else {
            break;
        }
    }
    printf(BROWN "\nPress any key to return to the Main Menu..." RESET);
    getchar();
    getchar();
    system("cls");
    gameMenu();
}

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
        printf(CYAN "\nEnter player 2 name: " RESET);
        scanf("%s", player2);
    } else {
        printf(CYAN "\nEnter player 1 name: " RESET);
        scanf("%s", player1);
        printf(CYAN "\nEnter player 2 name: " RESET);
        scanf("%s", player2);
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
                printf("%s", wordToGuess);
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
        if (!isGuest) {
            if (player1Score > player.highScore) {
                player.highScore = player1Score;
                saveProgress();
            }
            if (wins > player.streak) {
                player.streak = wins;
                saveProgress();
            }
            player.streakBroken = 0;
        }
        PlaySound("win.wav", NULL, SND_FILENAME | SND_SYNC);
        Sleep(2000);
        winAnimation();
    } else if (player2Score > player1Score) {
        printf(GREEN "\n%s wins!\n" RESET, player2);
        if (!isGuest) player.streakBroken = 1;
        PlaySound("win.wav", NULL, SND_FILENAME | SND_SYNC);
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

void timeAttackMode() {
    int totalScore = 0;

    system("cls");
    printf(ROYAL_BLUE "\n<-------TIME ATTACK MODE------->\n" RESET);
    printf(PINK "You have 3 minutes to guess as many words as you can!\n" RESET);
    printf(PINK "Each correct guess earns points. Let's see how many you can get!\n" RESET);
    printf(BROWN "\nPress any key to start..." RESET);
    getchar();
    getchar();
    system("cls");

    if (player.level >= 3) {
        revealLetter = true;
    }

    printf(ROYAL_BLUE "\n-------LEVEL %d-------\n" RESET, player.level);
    printf(CYAN "-------GAME %d-------\n" RESET, player.game);
    printf(PINK "\n----THEMES----\n" RESET);
    for (int i = 0; i < MAX_THEMES; i++) {
        printf("%d. %s\n", i + 1, levels[player.level - 1].themes[i].name);
    }
    printf(BROWN "\nPress ESC to quit, or SPACE to go back to the Game Mode Menu.\n" RESET);
    printf(PURPLE "\nChoose a theme: " RESET);
    int key = _getch();
    if (key == 27) {
        int response = MessageBox(NULL,"Are you sure you want to quit?","Exit Confirmation",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
        
        if (response == IDYES) {
            system("cls");
            printf(DARK_PINK "\nLeaving the game" RESET);
            for (int i = 0; i < 3; i++) {
                Sleep(300);
                printf(DARK_PINK "." RESET);
                fflush(stdout);
            }
            exit(0);
        }
    } else if (key == 32) {
        system("cls");
        gameModeMenu();
        while (getchar() != '\n');
    }
    while (scanf("%d", &themeChoice) != 1 || themeChoice < 1 || themeChoice > MAX_THEMES) {
        printf(RED "\nInvalid input. Enter one of the option numbers on screen.\n" RESET);
        printf(PURPLE "\nChoose a theme: " RESET);
        while (getchar() != '\n');
    }
    system("cls");

    time(&startTime);

    while (true) {
        memset(guessed, '\0', sizeof(guessed));
        tries = 0;
        correctGuessCount = 0;
        gameOver = false;
        hintTaken = false;

        srand(time(0));
        wordIndex = rand() % WORD_COUNT;
        const char *word = levels[player.level - 1].themes[themeChoice - 1].words[wordIndex];

        while (!gameOver) {
            system("cls");
            time(&currentTime);
            remainingTime = 180 - (int)difftime(currentTime, startTime);
            if (remainingTime <= 0) {
                if (!isGuest) {
                    if (wins > player.streak) {
                        player.streak = wins;
                    }
                    saveProgress();
                }
                printf(RED BOLD "\nTIME'S UP!\n" RESET);
                printf(CREAM BOLD "\nYour total score: %d\n" RESET, totalScore);
                if (player.streak >= 5 && player.streakBadge == 0 && !isGuest) {
                    awardBadge(7);
                    player.streakBadge = 1;
                }
                if (totalScore >= 100 || wins >= 7) {
                    if (!isGuest && player.timeBadge == 0) {
                        awardBadge(8);
                        player.timeBadge = 1;
                    }
                }
                printf(BROWN "\nPress any key to return to the Game Menu..." RESET);
                getchar();
                getchar();
                system("cls");
                gameMenu();
                break;
            }
            printf(YELLOW BOLD "\nTime Remaining: %d seconds\n" RESET, remainingTime);
            displayHintMeter(3, hintCount);
            displayHangman(tries);
            if (hintTaken && hintCount <= 3) {
                printf(YELLOW "\nHint: %s\n\n" RESET, levels[player.level-1].themes[themeChoice-1].hints[wordIndex]);
            }

            for (int i = 0; i < strlen(word); i++) {
                if (revealLetter && i == 0) {
                    guessed[i] = word[i];
                    printf("%c ", toupper(word[i]));
                } else if (word[i] == ' ') {
                    printf("  ");
                } else if (guessed[i] != '\0') {
                    printf("%c ", toupper(guessed[i]));
                } else {
                    printf("__ ");
                }
            }

            printf(PURPLE "\n\nGuess a letter: " RESET);
            scanf(" %c", &guessedLetter);
            while (!isalpha(guessedLetter)) {
                printf(RED "\nInvalid input! Please enter a letter." RESET);
                printf(PURPLE "\n\nGuess a letter: " RESET);
                scanf(" %c", &guessedLetter);
            }

            bool found = false;
            if (!revealLetter) {
                for (int i = 0; i < strlen(word); i++) {
                    if (toupper(word[i]) == toupper(guessedLetter)) {
                        guessed[i] = word[i];
                        found = true;
                        correctGuessCount++;
                    }
                }
            } else {
                for (int i = 0; i < strlen(word); i++) {
                    if (toupper(word[i]) == toupper(guessedLetter)) {
                        guessed[i] = word[i];
                        found = true;
                    }
                }
                correctGuessCount = 0;
                for (int i = 0; i < strlen(guessed); i++) {
                    if (guessed[i] != '\0') {
                        correctGuessCount++;
                    }
                }
            }

            if (!found) {
                system("cls");
                tries++;
                time(&currentTime);
                remainingTime = 180 - (int)difftime(currentTime, startTime);
                printf(YELLOW BOLD "\nTime Remaining: %d seconds\n" RESET, remainingTime);
                displayHintMeter(3, hintCount);
                displayHangman(tries);
                if (hintTaken && hintCount <= 3) {
                    printf(YELLOW "\nHint: %s\n\n" RESET, levels[player.level-1].themes[themeChoice-1].hints[wordIndex]);
                }
                for (int i = 0; i < strlen(word); i++) {
                    if (word[i] == ' ') {
                        printf("  ");
                    } else if (guessed[i] != '\0') {
                        printf("%c ", toupper(guessed[i]));
                    } else {
                        printf("__ ");
                    }
                }
                printf(RED "\n\nThe letter '%c' is not in the word." RESET, guessedLetter);
                Sleep(800);
                system("cls");
            }

            if (correctGuessCount == strlen(word)) {
                system("cls");
                displayHangman(tries);
                for (int i = 0; i < strlen(word); i++) {
                    printf("%c ", toupper(guessed[i]));
                }
                printf(GREEN BOLD "\n\nYOU GUESSED THE WORD!\n" RESET);
                wins++;
                calculateScore();
                totalScore += score;
                if (!isGuest) {
                    if (wins > player.streak) {
                        player.streak = wins;
                    }
                    player.streakBroken = 0;
                    saveProgress();
                }
                Sleep(2000);
                gameOver = true;
            } else if (tries == MAX_TRIES) {
                system("cls");
                wins = 0;
                displayHangman(tries);
                printf(YELLOW "\nThe word was: %s\n" RESET, word);
                printf(RED BOLD "\nYOU FAILED TO GUESS THE WORD!\n" RESET);
                if (!isGuest) {
                    player.streakBroken = 1;
                    saveProgress();
                }
                Sleep(2000);
                gameOver = true;
            }

            if (tries == 3 && !gameOver && !hintTaken) {
                offerHint();
            }
        }
    }
}

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
            printf(YELLOW "\nHint: %s\n\n" RESET,levels[player.level-1].themes[themeChoice-1].hints[wordIndex]);
            if (hintCount == 3) {
                printf(RED "\nYou have run out of hints\n" RESET);
            }
            Sleep(2000);
        }
        system("cls");
    }
}

void displayHangman(int tries) {
    const char *hangman[] = {
        "     +---+\n"
        "     |   |\n"
        "         |\n"
        "         |\n"
        "         |\n"
        "         |\n"
        "  =========\n\n",

        "     +---+\n"
        "     |   |\n"
        "     O   |\n"
        "         |\n"
        "         |\n"
        "         |\n"
        "  =========\n\n",

        "     +---+\n"
        "     |   |\n"
        "     O   |\n"
        "     |   |\n"
        "         |\n"
        "         |\n"
        "  =========\n\n",

        "     +---+\n"
        "     |   |\n"
        "     O   |\n"
        "    /|   |\n"
        "         |\n"
        "         |\n"
        "  =========\n\n",

        "     +---+\n"
        "     |   |\n"
        "     O   |\n"
        "    /|\\  |\n"
        "         |\n"
        "         |\n"
        "  =========\n\n",

        "     +---+\n"
        "     |   |\n"
        "     O   |\n"
        "    /|\\  |\n"
        "    /    |\n"
        "         |\n"
        "  =========\n\n",

        "     +---+\n"
        "     |   |\n"
        "     O   |\n"
        "    /|\\  |\n"
        "    / \\  |\n"
        "         |\n"
        "  =========\n\n"
    };

    printf("%s", hangman[tries]);
}

void calculateScore() {
    score += (5*correctGuessCount);
    score -= (1*tries);
    if (hintTaken) {
        score-=3;
    }
    printf(CREAM BOLD "\n\nYour score: %d\n\n" RESET, score);

    if (score > player.highScore) {
        player.highScore = score;
    }
}

void saveProgress() {
    char tempName[MAX_LENGTH];
    int tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, tempB4;

    FILE *file = fopen("stats.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    while (fscanf(file, "%s %d %d %d %d %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken, &tempB1, &tempB2, &tempB3, &tempB4) != EOF) {
        if (strcmp(tempName, player.name) == 0) {
            fprintf(tempFile, "%s %d %d %d %d %d %d %d %d %d\n", player.name, player.streak, player.highScore, player.level, player.game, player.streakBroken, player.hintBadge, player.speedBadge, player.streakBadge, player.timeBadge);
        } else {
            fprintf(tempFile, "%s %d %d %d %d %d %d %d %d %d\n", tempName, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, tempB4);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("stats.txt");
    rename("temp.txt", "stats.txt");
}

void awardBadge(int badgeIndex) {
    if (badgeIndex < 0 || badgeIndex >= MAX_BADGES) {
        return;
    }
    if (!isGuest) {
        printf(ROYAL_BLUE "\nCongratulations! You have earned the " RESET);
        printf("\"%s\"", badges[badgeIndex]);
        printf(ROYAL_BLUE " badge.\n" RESET);
        Sleep(2000);
    }
    return;
}

void levelCompleted() {
    printf(GREEN BOLD "\nCONGRATULATIONS! You have completed Level %d\n" RESET, player.level);
    switch (player.level) {
        case 1:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Rookie Rambler\"!\n" RESET);
            awardBadge(0);
            break;
        case 2:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Casual Challenger\"!\n" RESET);
            awardBadge(1);
            break;
        case 3:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Puzzle Pro\"!\n" RESET);
            awardBadge(2);
            break;
        case 4:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Mind Master\"!\n" RESET);
            awardBadge(3);
            break;
        case 5:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Hangman Hero\"!\n" RESET);
            awardBadge(4);
            break;
        default:
            printf(ROYAL_BLUE BOLD "\nYou have now officially mastered this game!\n GOODBYE :)\n" RESET);
            awardBadge(9);
    }
}

void leaderboard() {
    typedef struct {
        char name[MAX_LENGTH];
        int highScore;
    } PlayerStats;

    PlayerStats players[100];
    int playerCount = 0;

    for (int i = 0; i < 100; i++) {
        players[i].name[0] = '\0';
        players[i].highScore = 0;
    }

    FILE *file = fopen("stats.txt", "r");
    if (file == NULL) {
        printf(RED "\nError opening stats file!\n" RESET);
        return;
    }

    while (fscanf(file, "%s %*d %d %*d %*d %*d %*d %*d %*d", players[playerCount].name, &players[playerCount].highScore) != EOF) {
        playerCount++;
    }
    fclose(file);

    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = i + 1; j < playerCount; j++) {
            if (players[i].highScore < players[j].highScore) {
                PlayerStats temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf(CYAN BOLD "\n<-------LEADERBOARD------->\n" RESET);
    printf(YELLOW BOLD "\n%-5s %-20s %-10s\n" RESET, "Rank", "Player Name", "High Score");
    printf(YELLOW "-----------------------------------\n" RESET);

    for (int i = 0; i < playerCount && i < 10; i++) {
        printf(GREEN "%-5d %-20s %-10d\n" RESET, i + 1, players[i].name, players[i].highScore);
    }

    printf(BROWN "\nPress any key to return to the Main Menu..." RESET);
    getchar();
    getchar();
    system("cls");
}

void populateLevels() {
    {
        const char *themeList[MAX_THEMES] = {"FOOD", "ANIMAL", "OBJECT", "SPORT", "CITY"};

        const char *wordLists[MAX_THEMES][WORD_COUNT] = {
            {"APPLE", "BANANA", "MILK", "PEAR", "BREAD", "HAM", "CAKE", "PIE", "TEA", "COFFEE"},
            {"DOG", "CAT", "ANT", "BAT", "DEER", "BEAR", "DUCK", "GOAT", "COW", "SHEEP"},
            {"BELL", "CUP", "CHAIR", "PHONE", "LAMP", "BOOK", "CLOCK", "BAG", "SHOE", "GLASS"},
            {"FOOTBALL", "DANCE", "TENNIS", "CRICKET", "BASEBALL", "GOLF", "SWIMMING", "CYCLING", "CHESS", "BOXING"},
            {"NEW YORK", "LONDON", "PARIS", "TOKYO", "SYDNEY", "DHAKA", "ROME", "DUBAI", "MILAN", "DELHI"}
        };
        const char *hintLists[MAX_THEMES][WORD_COUNT] = {
            {"A fruit that keeps the doctor away", 
            "A yellow fruit loved by monkeys", 
            "A dairy product often added to tea or coffee", 
            "A green or brown fruit with a sweet taste", 
            "A staple food made from flour", 
            "A type of cured meat", 
            "A sweet baked dessert", 
            "A dessert with a crust and filling",
            "A hot beverage made from leaves", 
            "A hot beverage made from beans"},

            {"Man's best friend", 
            "A common pet that purrs", 
            "A small insect that works in colonies", 
            "A flying mammal", 
            "A graceful forest animal with antlers", 
            "A large mammal found in forests", 
            "A water bird that quacks", 
            "A farm animal known for its milk", 
            "A farm animal that gives milk and beef", 
            "A wool-producing farm animal"},

            {"Rings when pressed", 
            "Used to drink liquids", 
            "Furniture to sit on", 
            "Used to make calls", 
            "Provides light in a room", 
            "Used for reading", 
            "Shows the time", 
            "Used to carry items", 
            "Worn on feet", 
            "Used to drink water"},
        
            {"A game played with a round ball and goals", 
            "A rhythmic activity performed to music", 
            "A racket sport played on a court", 
            "A bat-and-ball game popular in South Asia", 
            "A bat-and-ball game popular in the USA", 
            "A sport played on a course with clubs", 
            "A water-based activity", 
            "A two-wheeled activity", 
            "A board game of strategy", 
            "A combat sport with gloves"},
        
            {"The Big Apple", 
            "Capital of the United Kingdom", 
            "The City of Light", 
            "Capital of Japan", 
            "Famous for its Opera House", 
            "Capital of Bangladesh", 
            "The Eternal City", 
            "Known for its skyscrapers and luxury", 
            "Fashion capital of Italy", 
            "Capital of India"}
        };

        addLevel(themeList, wordLists, hintLists);
    }

    {
        const char *themeList[MAX_THEMES] = {"FOOD", "ANIMAL", "SPORT", "CITY", "COLOUR"};

        const char *wordLists[MAX_THEMES][WORD_COUNT] = {
            {"RAMEN", "HONEY", "YOGURT", "STEAK", "CHEESE", "CEREAL", "PANCAKE", "PUMPKIN", "CUCUMBER", "PINEAPPLE"},
            {"PANDA", "MOUSE", "ELEPHANT", "TIGER", "SHARK", "WOLF", "MONKEY", "SNAKE", "CAMEL", "FROG"},
            {"SOCCER", "JUDO", "HOCKEY", "RUGBY", "SKATING", "WRESTLING", "BADMINTON", "BOWLING", "FENCING", "VOLLEYBALL"},
            {"MILAN", "CAIRO", "TORONTO", "BANGKOK", "CHICAGO", "MANILA", "KARACHI", "BERLIN", "FLORENCE", "MADRID"},
            {"AQUA", "BEIGE", "GOLD", "GREY", "CYAN", "SILVER", "TEAL", "IVORY", "INDIGO", "LAVENDER"}
        };
        const char *hintLists[MAX_THEMES][WORD_COUNT] = {
            
            {"A Japanese noodle soup dish", 
            "A sweet substance made by bees", 
            "A creamy dairy product often eaten with fruits", 
            "A cut of meat, often grilled or fried", 
            "A dairy product used in sandwiches and pizzas", 
            "A breakfast food made from grains", 
            "A flat, round breakfast food often served with syrup", 
            "A large orange vegetable used in pies", 
            "A green vegetable often used in salads", 
            "A tropical fruit with spiky skin and sweet yellow flesh"},
        
            {"A black-and-white bear that eats bamboo", 
            "A small rodent often kept as a pet", 
            "A large mammal with a trunk", 
            "A striped big cat", 
            "A predatory fish with sharp teeth", 
            "A wild canine known for its howl", 
            "A primate that loves bananas", 
            "A legless reptile", 
            "A desert animal with a hump", 
            "An amphibian that hops and croaks"},
        
            {"A game played with a round ball and goals", 
            "A martial art originating from Japan", 
            "A sport played on ice or a field with a stick", 
            "A contact sport played with an oval ball", 
            "A sport performed on ice with blades", 
            "A combat sport involving grappling", 
            "A racket sport played on a court", 
            "A game played by rolling a ball to knock down pins", 
            "A sport involving swords and protective gear", 
            "A team sport played with a net and a ball"},
        
            {"A fashion capital in Italy", 
            "The capital of Egypt", 
            "A major Canadian city", 
            "The capital of Thailand", 
            "A windy city in the USA", 
            "The capital of the Philippines", 
            "A populous city in Pakistan", 
            "The capital of Germany", 
            "A historic city in Italy known for art", 
            "The capital of Spain"},
        
            {"A shade of blue-green", 
            "A pale brown color", 
            "A precious metal color", 
            "A neutral shade between black and white", 
            "A bright blue-green color", 
            "A shiny gray-white metal color", 
            "A dark greenish-blue color", 
            "A creamy white color", 
            "A deep blue-purple color", 
            "A pale purple color"},
        };

        addLevel(themeList, wordLists, hintLists);
    }

    {
        const char *themeList[MAX_THEMES] = {"TECH", "ANIMAL", "CHARACTER", "CITY", "MATHS"};

        const char *wordLists[MAX_THEMES][WORD_COUNT] = {
            {"CLOUD", "JAVA", "ROUTER", "PIXEL", "SERVER", "BROWSER", "PYTHON", "INTERNET", "HACK", "DATABASE"},
            {"OWL", "VULTURE", "CHAMELEON", "CROCODILE", "HIPPOPOTAMUS", "PORCUPINE", "TURTLE", "RABBIT", "JAGUAR", "DOLPHIN"},
            {"HARRY POTTER", "YODA", "BATMAN", "THOR", "FRODA", "IRON MAN", "SHERLOCK", "HULK", "LOKI", "DUMBLEDORE"},
            {"KYOTO", "OSAKA", "SEOUL", "LAGOS", "VIENNA", "SANTIAGO", "SACRAMENTO", "NAIROBI", "AGRA", "PERTH"},
            {"ALGEBRA", "CALCULUS", "GEOMETRY", "FRACTION", "RATIO", "ANGLE", "EQUATION", "FUNCTION", "STATISTICS", "PARALLEL"}
        };
        const char *hintLists[MAX_THEMES][WORD_COUNT] = {
            {"A virtual storage system", 
            "A popular programming language", 
            "A device that directs network traffic", 
            "A small unit of a digital image", 
            "A computer that provides data to other computers", 
            "A software application for accessing the web", 
            "A programming language named after a snake", 
            "A global network connecting millions of devices", 
            "An unauthorized attempt to access data", 
            "A structured collection of data"},
        
            {"A nocturnal bird known for its hooting sound", 
            "A large bird of prey with a bald head", 
            "A reptile that can change its color", 
            "A large reptile with a powerful bite", 
            "A large, semi-aquatic mammal", 
            "A spiny mammal that rolls into a ball for defense", 
            "A slow-moving reptile with a shell", 
            "A small mammal known for its long ears", 
            "A large cat found in rainforests", 
            "A highly intelligent marine mammal"},
        
            {"The boy who lived in the wizarding world", 
            "A wise Jedi master from Star Wars", 
            "A superhero who fights crime in Gotham City", 
            "The Norse god of thunder", 
            "A hobbit from The Lord of the Rings", 
            "A genius billionaire superhero in a suit", 
            "A brilliant detective from Baker Street", 
            "A green superhero with immense strength", 
            "The god of mischief from Norse mythology", 
            "The headmaster of Hogwarts School of Witchcraft and Wizardry"},
        
            {"A historic city in Japan known for its temples", 
            "A major city in Japan known for its food and culture", 
            "The capital of South Korea", 
            "The largest city in Nigeria", 
            "The capital of Austria", 
            "The capital of Chile", 
            "The capital of California, USA", 
            "The capital of Kenya", 
            "A historic city in India known for the Taj Mahal", 
            "A major city in Western Australia"},
        
            {"A branch of mathematics dealing with equations", 
            "A branch of mathematics involving limits and derivatives", 
            "A branch of mathematics dealing with shapes and sizes", 
            "A part of a whole expressed as a ratio", 
            "A comparison of two quantities", 
            "A measure of the space between two lines", 
            "A mathematical statement showing equality", 
            "A relation between inputs and outputs", 
            "A branch of mathematics dealing with data analysis", 
            "Two lines that never meet"}
        };

        addLevel(themeList, wordLists, hintLists);
    }

    {
        const char *themeList[MAX_THEMES] = {"SCIENCE", "HARRY POTTER", "BOOK TITLE", "COUNTRY", "MOVIE"};

        const char *wordLists[MAX_THEMES][WORD_COUNT] = {
            {"CHEMISTRY", "PHYSICS", "BIOLOGY", "BEAKER", "BOTANY", "GEOLOGY", "ATOM", "MOLECULE", "ELEMENT", "COMPOUND"},
            {"SNAPE", "RON", "WEASLEY", "NEVILLE", "GRYFFINDOR", "SLYTHERIN", "DOBBY", "LUPIN", "NIMBUS", "HAGRID"},
            {"MOBY DICK", "THE HOBBIT", "THE BOOK THIEF", "THE SHINING", "1984", "CATCH 22", "LITTLE WOMEN", "PRIDE AND PREJUDICE", "ROMEO JULIET", "THE ALCHEMIST"},
            {"ARGENTINA", "CHINA", "KOREA", "JAPAN", "THAILAND", "CANADA", "GERMANY", "RUSSIA", "GREECE", "COLOMBIA"},
            {"TITANIC", "AVATAR", "INCEPTION", "PARASITE", "FROZEN", "TOY STORY", "GLADIATOR", "LA LA LAND", "UP", "COCO"}
        };
        const char *hintLists[MAX_THEMES][WORD_COUNT] = {
            {"The study of matter and its interactions", 
            "The study of energy and forces", 
            "The study of living organisms", 
            "A container used in laboratories", 
            "The study of plants", 
            "The study of Earth's physical structure", 
            "The smallest unit of matter", 
            "A group of atoms bonded together", 
            "A pure substance made of one type of atom", 
            "A substance formed by combining two or more elements"},
        
            {"The potions master at Hogwarts", 
            "Harry's best friend with red hair", 
            "The last name of Harry's best friend", 
            "A brave and clumsy Gryffindor student", 
            "The house of bravery and courage", 
            "The house of cunning and ambition", 
            "A loyal house-elf", 
            "A werewolf and Defense Against the Dark Arts teacher", 
            "A type of broomstick used for flying", 
            "The half-giant gamekeeper at Hogwarts"},
        
            {"A novel about a white whale", 
            "A fantasy novel about a hobbit's journey", 
            "A story about a girl who steals books during WWII", 
            "A horror novel by Stephen King", 
            "A dystopian novel by George Orwell", 
            "A satirical novel about war", 
            "A classic novel about four sisters", 
            "A romantic novel by Jane Austen", 
            "A tragic love story by Shakespeare", 
            "A philosophical novel by Paulo Coelho"},
        
            {"A South American country known for tango", 
            "The most populous country in the world", 
            "A country divided into North and South", 
            "An island nation in East Asia", 
            "A Southeast Asian country known for its beaches", 
            "A North American country known for maple syrup", 
            "A European country known for its engineering", 
            "The largest country in the world", 
            "A European country known for its ancient history", 
            "A South American country known for coffee"},
        
            {"A romantic movie about a shipwreck", 
            "A sci-fi movie set on Pandora", 
            "A mind-bending thriller by Christopher Nolan", 
            "An Oscar-winning South Korean film", 
            "A Disney movie about a magical ice queen", 
            "A Pixar movie about toys coming to life", 
            "A historical epic about a Roman general", 
            "A musical romance set in Los Angeles", 
            "A Pixar movie about a house lifted by balloons", 
            "A Pixar movie about a boy and the Land of the Dead"},
        };

        addLevel(themeList, wordLists, hintLists);
    }

    {
        const char *themeList[MAX_THEMES] = {"HARRY POTTER", "MYTHOLOGY", "INVENTORS", "K-POP", "TV SHOW"};

        const char *wordLists[MAX_THEMES][WORD_COUNT] = {
            {"MARAUDER", "SNITCH", "RAVENCLAW", "HUFFLEPUFF", "SIRIUS", "MALFOY", "QUIDDITCH", "HONEYDUKES", "CRUCIO", "PETRIFICUS TOTALUS"},
            {"ZEUS", "POSEIDON", "ATHENA", "ARES", "DIONYSUS", "ODIN", "THOR", "ANUBIS", "RA", "HORUS"},
            {"EINSTEIN", "NEWTON", "MARIE CURIE", "GALILEO", "TESLA", "DARWIN", "HAWKING", "MENDLEEV", "PASTEUR", "BOHR"},
            {"BTS", "BLACKPINK", "TWICE", "EXO", "IVE", "STRAY KIDS", "SEVENTEEN", "RED VELVET", "ITZY", "AESPA"},
            {"FRIENDS", "BREAKING BAD", "STRANGER THINGS", "LUCIFER", "MODERN FAMILY", "HOUSE", "THE FLASH", "EUPHORIA", "GILMORE GIRLS", "GOSSIP GIRLS"}
        };
        const char *hintLists[MAX_THEMES][WORD_COUNT] = {
            {"A group of mischievous map creators", 
            "A golden ball used in Quidditch", 
            "The house of wit and learning", 
            "The house of loyalty and hard work", 
            "Harry's godfather", 
            "A cunning and ambitious wizarding family", 
            "A popular wizarding sport", 
            "A sweet shop in Hogsmeade", 
            "A curse that causes immense pain", 
            "A spell that paralyzes the target"},
        
            {"The king of the Greek gods", 
            "The Greek god of the sea", 
            "The Greek goddess of wisdom and war", 
            "The Greek god of war", 
            "The Greek god of wine and revelry", 
            "The Norse god of wisdom and magic", 
            "The Norse god of thunder", 
            "The Egyptian god of the afterlife", 
            "The Egyptian sun god", 
            "The Egyptian god of the sky"},
        
            {"The physicist who developed the theory of relativity", 
            "The mathematician who formulated the laws of motion", 
            "The scientist who discovered radioactivity", 
            "The astronomer who supported the heliocentric model", 
            "The inventor of the alternating current system", 
            "The naturalist who proposed the theory of evolution", 
            "The physicist who studied black holes", 
            "The chemist who created the periodic table", 
            "The scientist who developed pasteurization", 
            "The physicist who developed quantum theory"},
        
            {"A globally famous boy band from South Korea", 
            "A girl group known for 'Kill This Love'", 
            "A girl group known for 'Fancy'", 
            "A boy group known for their powerful performances", 
            "A girl group known for 'Love Dive'", 
            "A boy group known for 'God's Menu'", 
            "A boy group with 13 members", 
            "A girl group known for 'Psycho'", 
            "A girl group known for 'Dalla Dalla'", 
            "A girl group known for 'Next Level'"},
        
            {"A sitcom about six friends in New York", 
            "A drama about a chemistry teacher turned drug lord", 
            "A sci-fi show about kids in Hawkins, Indiana", 
            "A show about the devil running a nightclub", 
            "A sitcom about a dysfunctional family", 
            "A medical drama about a brilliant but flawed doctor", 
            "A superhero show about the fastest man alive", 
            "A teen drama about high school students", 
            "A show about a mother and daughter duo", 
            "A drama about the lives of wealthy teenagers"},
        };

        addLevel(themeList, wordLists, hintLists);
    }
}

void gameModeMenu() {
    int modeChoice;

    printf(LAVENDER "\n<-------GAME MODE MENU------->\n" RESET);
    printf(GREEN "1. Normal Mode\n" RESET);
    printf(YELLOW "2. Time Challenge Mode\n" RESET);
    printf(PINK "3. Multiplayer Mode\n" RESET);
    printf(ROYAL_BLUE "4. Time Attack Mode\n" RESET);
    printf(ORANGE "5. Go Back\n" RESET);
    printf(PURPLE "Choose an option: " RESET);

    while (scanf("%d", &modeChoice) != 1) {
        printf(RED "\nInvalid input! Please enter a number.\n" RESET);
        while (getchar() != '\n');
        printf(PURPLE "\nChoose an option: " RESET);
    }

    switch (modeChoice) {
        case 1:
            printf(GREEN "\nYou have chosen Normal Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            break;
        case 2:
            printf(YELLOW "\nYou have chosen Time Challenge Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            timeChallengeMode();
            break;
        case 3:
            printf(PINK "\nYou have chosen Multiplayer Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            multiplayerMode();
            break;
        case 4:
            printf(ROYAL_BLUE "\nYou have chosen Time Attack Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            timeAttackMode();
            break;
        case 5:
            system("cls");
            gameMenu();
            break;
        default:
            printf(RED "\nInvalid choice. Please select a valid game mode.\n" RESET);
            Sleep(1000);
            system("cls");
            gameModeMenu();
            break;
    }
}

void gameMenu() {
    int choice;

    printf(BLINK PASTEL_PURPLE "\n~~~~~~~ MAIN MENU ~~~~~~~\n" RESET);
    if (isGuest) {
        printf(PASTEL_PINK "1. Start Game\n" RESET);
        printf(PASTEL_BLUE "2. Instructions\n" RESET);
        printf(PASTEL_ORANGE "3. Leaderboard\n" RESET);
        printf(PASTEL_MINT "4. Credits\n" RESET);
        printf(PASTEL_LIME "5. Leave\n" RESET);
        printf(PASTEL_TURQUOISE "Enter Your Choice: " RESET);
    } else {
        printf(PASTEL_PINK "1. Start New Game\n" RESET);
        printf(PASTEL_SALMON "2. Resume Game\n" RESET);
        printf(PASTEL_YELLOW "3. View Profile\n" RESET);
        printf(PASTEL_BLUE "4. Instructions\n" RESET);
        printf(PASTEL_ORANGE "5. Leaderboard\n" RESET);
        printf(PASTEL_MINT "6. Credits\n" RESET);
        printf(PASTEL_LIME "7. Log Out\n" RESET);
        printf(PASTEL_TURQUOISE "Enter Your Choice: " RESET);
    }
    fflush(stdout);
    while (scanf("%d", &choice) != 1) {
        printf(RED "\nInvalid input! Please enter a number.\n" RESET);
        while (getchar() != '\n');
        printf(PASTEL_TURQUOISE "Enter Your Choice: " RESET);
    }

    if (isGuest) {
        switch (choice) {
            case 1:
                system("cls");
                player.level = 1;
                player.game = 1;
                gameModeMenu();
                return;
            case 2:
                system("cls");
                typeEffect("\nYour task is to guess the word before the stickman is fully hanged.\n", OLIVE_GREEN);
                typeEffect("There are five levels in this game.\n", SAND_BEIGE);
                typeEffect("You can choose the theme for each stages.\n", FOREST_GREEN);
                typeEffect("You'll get an option for hint after 3 incorrect guesses in each game.\n", CLAY_BROWN);
                typeEffect("However...You only have 3 hints throughout one game-play session.\n", KHAKI);
                typeEffect("+5 points will be added for each correct guess.\n", DEEP_MOSS);
                typeEffect("3 points will be deducted for using a hint.\n", DUSTY_ROSE);
                typeEffect("1 points will be deducted for each incorrect guess.\n", BURNT_UMBER);
                typeEffect("Maximum wrong guesses: 6\n", BARK_BROWN);
                typeEffect("Good Luck!", HBLK);
                printf(BROWN "\n\nPress any key to go back..." RESET);
                getchar();
                getchar();
                system("cls");
                gameMenu();
                break;
            case 3:
                system("cls");
                leaderboard();
                system("cls");
                gameMenu();
                break;
            case 4:
                printf(PASTEL_PEACH "\n~~~~~~~CREDITS~~~~~~~\n" RESET);
                waveText("1. Priyonti Tabassum Haque", ROYAL_BLUE, CYAN);
                waveText("2. Sumaiya Yasmin Nairit", RED, ORANGE);
                waveText("3. Dizzya Al Fahad", DUSTY_ROSE, TERRACOTTA);
                waveText("4. Avishek Saha", YELLOW, GREEN);
                printf(BROWN "\n\nPress any key to go back..." RESET);
                getchar();
                getchar();
                system("cls");
                gameMenu();
                break;
            case 5: {
                int response = MessageBox(NULL, "Are you sure you want to quit?", "Exit Confirmation", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);

                if (response == IDYES) {
                    system("cls");
                    printf(DARK_PINK "\nLeaving" RESET);
                    for (int i = 0; i < 3; i++) {
                        Sleep(300);
                        printf(DARK_PINK "." RESET);
                        fflush(stdout);
                    }
                    exit(0);
                } else {
                    system("cls");
                    gameMenu();
                }
                break;
            }
            default:
                printf(RED "\nInvalid number. Enter one of the option numbers on screen.\n" RESET);
                gameMenu();
                break;
        }
    } else {
        switch (choice) {
            case 1:
                system("cls");
                player.level = 1;
                player.game = 1;
                gameModeMenu();
                return;
            case 2:
                system("cls");
                gameModeMenu();
                return;
            case 3:
                system("cls");
                playerDetails();
                return;
            case 4:
                system("cls");
                typeEffect("\nYour task is to guess the word before the stickman is fully hanged.\n", OLIVE_GREEN);
                typeEffect("There are five levels in this game.\n", SAND_BEIGE);
                typeEffect("You can choose the theme for each stages.\n", FOREST_GREEN);
                typeEffect("You'll get an option for hint after 3 incorrect guesses in each game.\n", CLAY_BROWN);
                typeEffect("However...You only have 3 hints throughout one game-play session.\n", KHAKI);
                typeEffect("+5 points will be added for each correct guess.\n", DEEP_MOSS);
                typeEffect("3 points will be deducted for using a hint.\n", DUSTY_ROSE);
                typeEffect("1 points will be deducted for each incorrect guess.\n", BURNT_UMBER);
                typeEffect("Maximum wrong guesses: 6\n", BARK_BROWN);
                typeEffect("Good Luck!", HBLK);
                printf(BROWN "\n\nPress any key to go back..." RESET);
                getchar();
                getchar();
                system("cls");
                gameMenu();
                break;
            case 5:
                system("cls");
                leaderboard();
                system("cls");
                gameMenu();
                break;
            case 6:
                system("cls");
                printf(PASTEL_PEACH "\n~~~~~~~CREDITS~~~~~~~\n" RESET);
                waveText("1. Priyonti Tabassum Haque", ROYAL_BLUE, CYAN);
                waveText("2. Sumaiya Yasmin Nairit", RED, ORANGE);
                waveText("3. Dizzya Al Fahad", DUSTY_ROSE, TERRACOTTA);
                waveText("4. Avishek Saha", YELLOW, GREEN);
                printf(BROWN "\n\nPress any key to go back..." RESET);
                getchar();
                getchar();
                system("cls");
                gameMenu();
                break;
            case 7: {
                int response = MessageBox(NULL, "Are you sure you want to quit?", "Exit Confirmation", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);

                if (response == IDYES) {
                    system("cls");
                    printf(DARK_PINK "\nLeaving the game" RESET);
                    for (int i = 0; i < 3; i++) {
                        Sleep(300);
                        printf(DARK_PINK "." RESET);
                        fflush(stdout);
                    }
                    exit(0);
                } else {
                    system("cls");
                    gameMenu();
                }
                break;
            }
            default:
                printf(RED "\nInvalid number. Enter one of the option numbers on screen.\n" RESET);
                gameMenu();
                break;
        }
    }
}

void main() {

    populateLevels();

    playerMenu();
    Sleep(800);
    system("cls");

    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~\n" RESET);
    printf(CYAN "~~~~~~~~~~~~~~~~~~~~\n" RESET);
    printf(CREAM " WELCOME TO HANGMAN\n" RESET);
    printf(CYAN "~~~~~~~~~~~~~~~~~~~~\n" RESET);
    printf(CYAN "~~~~~~~~~~~~~~~~~~~~\n" RESET);
    gameMenu();
    system("cls");

    
    while (player.level <= MAX_LEVELS && player.game <= MAX_GAMES) {
        tries = 0;
        correctGuessCount = 0;
        gameOver = false;
        hintTaken = false;
        memset(guessed, '\0', sizeof(guessed));

        if (player.level >= 3) {
            revealLetter = true;
        }

        printf(ROYAL_BLUE "\n-------LEVEL %d-------\n" RESET, player.level);
        printf(CYAN "-------GAME %d-------\n" RESET, player.game);
        printf(PINK "\n----THEMES----\n" RESET);
        for (int i = 0; i < MAX_THEMES; i++) {
            printf("%d. %s\n", i+1, levels[player.level-1].themes[i].name);
        }
        printf(BROWN "\nPress ESC to quit, or SPACE to go back to the Game Mode Menu.\n" RESET);
        printf(PURPLE "\nChoose a theme: " RESET);
        int key = _getch();
        if (key == 27) {
            int response = MessageBox(NULL,"Are you sure you want to quit?","Exit Confirmation",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
            
            if (response == IDYES) {
                system("cls");
                printf(DARK_PINK "\nLeaving the game" RESET);
                for (int i = 0; i < 3; i++) {
                    Sleep(300);
                    printf(DARK_PINK "." RESET);
                    fflush(stdout);
                }
                exit(0);
            }
        } else if (key == 32) {
            system("cls");
            gameModeMenu();
            while (getchar() != '\n');
            continue;
        }
        while (scanf("%d", &themeChoice) != 1) {
            printf(RED "\nInvalid input. Enter one of the option numbers on screen.\n" RESET);
            while (getchar() != '\n');
            continue;
            printf(PURPLE "\nChoose a theme: " RESET);
        }
        while (themeChoice < 1 || themeChoice > 5) {
            printf(RED "\nInvalid number. Enter one of the option numbers on screen.\n" RESET);
            printf(PURPLE "\nChoose a theme: " RESET);
            scanf("%d", &themeChoice);
        }
        Sleep(800);
        system("cls");

        srand(time(0));
        wordIndex = rand() % WORD_COUNT;
        word = levels[player.level-1].themes[themeChoice-1].words[wordIndex];

        time(&startTime);

        while (!gameOver) {
            system("cls");
            if (timeChallenge) {
                time(&currentTime);
                remainingTime = 60 - (int)difftime(currentTime, startTime);
                if (remainingTime <= 0) {
                    printf(RED BOLD "\nTIME'S UP!\n" RESET);
                    printf(RED BOLD "\nYOU LOSE!\n" RESET);
                    PlaySound("lose.wav", NULL, SND_FILENAME | SND_SYNC);
                    wins = 0;
                    if (player.age >= 13 || isGuest) loseAnimation();
                    calculateScore();
                    if (!isGuest) {
                        player.streakBroken = 1;
                        saveProgress();
                    }
                    Sleep(3000);
                    system("cls");
                    break;
                }
                printf(YELLOW BOLD "\nTime Remaining: %d seconds\n" RESET, remainingTime);
            }
            calculateScore();
            displayHintMeter(3, hintCount);
            displayHangman(tries);
            if (hintTaken && hintCount <= 3) {
                printf(YELLOW "\nHint: %s\n\n" RESET, levels[player.level-1].themes[themeChoice-1].hints[wordIndex]);
            }

            for (int i = 0; i < strlen(word); i++) {
                if (revealLetter && i == 0) {
                    guessed[i] = word[i];
                    printf("%c ", toupper(word[i]));
                } else if (word[i] == ' ') {
                    printf("  ");
                } else if (guessed[i] != '\0') {
                    printf("%c ", toupper(guessed[i]));
                } else {
                    printf("__ ");
                }
            }

            printf(PURPLE "\n\nGuess a letter: " RESET);
            scanf(" %c", &guessedLetter);
            while (!isalpha(guessedLetter)) {
                printf(RED "\nInvalid input! Please enter a letter." RESET);
                printf(PURPLE "\n\nGuess a letter: " RESET);
                scanf(" %c", &guessedLetter);
            }

            bool found = false;
            if (!revealLetter) {
                for (int i = 0; i < strlen(word); i++) {
                    if (toupper(word[i]) == toupper(guessedLetter)) {
                        guessed[i] = word[i];
                        found = true;
                        correctGuessCount++;
                    }
                }
            } else {
                for (int i = 0; i < strlen(word); i++) {
                    if (toupper(word[i]) == toupper(guessedLetter)) {
                        guessed[i] = word[i];
                        found = true;
                    }
                }
                correctGuessCount = 0;
                for (int i = 0; i < strlen(guessed); i++) {
                    if (guessed[i] != '\0') {
                        correctGuessCount++;
                    }
                }
            }

            if (!found) {
                system("cls");
                tries++;
                if (timeChallenge) {
                    time(&currentTime);
                    remainingTime = 60 - (int)difftime(currentTime, startTime);
                    printf(YELLOW BOLD "\nTime Remaining: %d seconds\n" RESET, remainingTime);
                }
                calculateScore();
                displayHintMeter(3, hintCount);
                displayHangman(tries);
                if (hintTaken && hintCount <= 3) {
                    printf(YELLOW "\nHint: %s\n\n" RESET, levels[player.level-1].themes[themeChoice-1].hints[wordIndex]);
                }
                for (int i = 0; i < strlen(word); i++) {
                    if (word[i] == ' ') {
                        printf("  ");
                    } else if (guessed[i] != '\0') {
                        printf("%c ", toupper(guessed[i]));
                    } else {
                        printf("__ ");
                    }
                }
                printf(RED "\n\nThe letter '%c' is not in the word." RESET, guessedLetter);
                Sleep(800);
                system("cls");
            }
    
            if (tries == MAX_TRIES || correctGuessCount == strlen(word)) {
                gameOver = true;
                if (correctGuessCount == strlen(word)) {
                    system ("cls");
                    displayHangman(tries);
                    for (int i = 0; i < strlen(word); i++) {
                        printf("%c ", toupper(guessed[i]));
                    }
                    printf(GREEN BOLD "\n\nYOU WIN!\n" RESET);
                    player.game++;
                    if (player.game > MAX_GAMES) {
                        player.game = 1;
                        player.level++;
                        if (hintCount == 0 && player.hintBadge == 0 && !isGuest) {
                            awardBadge(5);
                            player.hintBadge = 1;
                        }
                        if (timeChallenge && remainingTime > 30 && player.speedBadge == 0 && !isGuest) {
                            awardBadge(6);
                            player.speedBadge = 1;
                        }
                        levelCompleted();
                    }
                    wins++;
                    if (!isGuest) {
                        player.streakBroken = 0;
                        if (wins > player.streak) {
                            player.streak = wins;
                        }
                        saveProgress();
                    }
                    Sleep(2000);
                    PlaySound("win.wav", NULL, SND_FILENAME | SND_SYNC);
                    winAnimation();
                    calculateScore();
                    if (player.streak >= 5 && player.streakBadge == 0 && !isGuest) {
                        awardBadge(7);
                        player.streakBadge = 1;
                    }
                    Sleep(3000);
                    system("cls");
                } else {
                    system("cls");
                    displayHangman(tries);
                    PlaySound("lose.wav", NULL, SND_FILENAME | SND_SYNC);
                    printf(YELLOW "The word was: %s\n" RESET, word);
                    printf(RED BOLD "\nYOU LOSE!\n" RESET);
                    Sleep(1000);
                    wins = 0;
                    if (!isGuest) {
                        player.streakBroken = 1;
                        saveProgress();
                    }
                    if (player.age >= 13 || isGuest) loseAnimation();
                    calculateScore();
                    Sleep(2000);
                    system("cls");
                }
            }
            if (tries == 3 && !gameOver && !hintTaken) {
                offerHint();
            }
        }
    }
}
