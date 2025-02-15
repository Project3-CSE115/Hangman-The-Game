#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6
#define WORD_COUNT 6

const char *wordList[WORD_COUNT] = {"RAMEN","LAPTOP","KARAOKE","BOTTLE","FOOTBALL","GARDEN"};

void displayHangman(int attempts)
{
    const char *hangman[] =
    {
      "\n +----+\n   |  |\n      |\n      |\n      |\n      |\n=========\n",
      "\n +----+\n   |  |\n   O  |\n      |\n      |\n      |\n=========\n",
      "\n +----+\n   |  |\n   O  |\n   |  |\n      |\n      |\n=========\n",
      "\n +----+\n   |  |\n   O  |\n  /|  |\n      |\n      |\n=========\n",
      "\n +----+\n   |  |\n   O  |\n  /|\\ |\n      |\n      |\n=========\n",
      "\n +----+\n   |  |\n   O  |\n  /|\\ |\n  /   |\n      |\n=========\n",
      "\n +----+\n   |  |\n   O  |\n  /|\\ |\n  / \\ |\n      |\n=========\n"
    };
    printf("%s", hangman[attempts]);
}

void displaytitle()
{
   printf("\n~~~~~~~~~~~~~~~~~~\n");
    printf("     HANGMAN        \n");
    printf("~~~~~~~~~~~~~~~~~~\n\n");
}\

int main ()
{
    displaytitle();
    printf("Welcome to the HANGMAN game!\n");
    printf("Your task is to guess the word before the stickman is fully hanged.\n");
    printf("Maximum wrong guesses: 6\n");
    printf("Good Luck!");
    return 0;
}
