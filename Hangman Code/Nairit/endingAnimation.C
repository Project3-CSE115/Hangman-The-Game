#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define GRAY "\x1B[90m"
#define WHITE "\x1B[97m"
#define RESET   "\033[0m"
#define BLINK "\x1B[5m"


#define CLEAR "cls"
#define SLEEP(ms) Sleep(ms)

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

void animateText(const char *text, int delay);
void winAnimation(int score);
void loseAnimation(const char *word, int score);



void animateText(const char *text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
        Sleep(delay);
    }
}

void winAnimation(int score) {
    system("cls");
    printf(HIDE_CURSOR);


    FILE *f = fopen("D:\\hangmanown.c\\466133__humanoide9000__victory-fanfare.wav", "r");
    if (f) {
        fclose(f);
        PlaySound(TEXT("D:\\hangmanown.c\\466133__humanoide9000__victory-fanfare.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
    printf("\nScore: %d\n", score);
    Sleep(500);
    animateText("Play again? (y/n): ", 30);
    getchar();
    printf(SHOW_CURSOR);
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

void loseAnimation(const char *word, int score) {
    system("cls");
    printf(HIDE_CURSOR);
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

    FILE *f = fopen("D:\\hangmanown.c\\758695__robo9418__mega-lightning.wav", "r");
    if (f) {
        fclose(f);
        PlaySound(TEXT("D:\\hangmanown.c\\758695__robo9418__mega-lightning.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
    printf(RED);
    animateText("\nStruck Out! Game Over.\n", 40);
    f = fopen("D:\\hangmanown.c\\gameover.wav.wav", "r");
    if (f) {
        fclose(f);
        PlaySound(TEXT("D:\\hangmanown.c\\gameover.wav.wav"), NULL, SND_FILENAME | SND_ASYNC);

    }
    printf(RESET);
    printf("The word was: %s\n", word);
    printf("Score: %d\n", score);
    Sleep(500);
    animateText("Play again? (y/n): ", 30);
    getchar();
    printf(SHOW_CURSOR);
}
int main() {
    int won = 0; // 1 for win, 0 for loss

    if (won)
        winAnimation(20);
    else
        loseAnimation("MYSTERY",20);

    return 0;
}
