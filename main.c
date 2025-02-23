#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TRIES 6
#define WORD_COUNT 6

const char *wordList[WORD_COUNT] = {"RAMEN","LAPTOP","KARAOKE","BOTTLE","FOOTBALL","GARDEN"};

void displaytitle()
{
    printf("\n~~~~~~~~~~~~~~~~~~\n");
    printf("     HANGMAN        \n");
    printf("~~~~~~~~~~~~~~~~~~\n\n");
}

void displayWord(const char *word, const int *guessed)
{
    for(int i = 0; i < strlen(word); i++)
    {
        if (guessed[i])
        {
            printf("%c",word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

int main ()
{
    displaytitle();
    printf("Welcome to the HANGMAN game!\n");
    printf("Your task is to guess the word before the stickman is fully hanged.\n");
    printf("Maximum wrong guesses: 6\n");
    printf("Good Luck!\n");

    srand(time(0));

    const char *word = wordList[rand() % WORD_COUNT];
    int word_length = strlen(word);
    int guessed[word_length];
    memset(guessed, 0, sizeof(guessed));
    int tries = 0;
    int correct_guesses = 0;
    char guess;

    while (tries < MAX_TRIES)
    {
        //displayHangman(tries);
        displayWord(word, guessed);
        printf("Enter Your Guess:");
        scanf(" %c",&guess);
        guess = toupper(guess);
        int found = 0;
        for(int i = 0; i < word_length; i++)
        {
            if(word[i] == guess && !guessed[i])
            {
                guessed[i] = 1;
                found = 1;
                correct_guesses++;
            }
        }
        if(!found)
        {
            tries++;
            printf("Incorrect! You have %d tries left\n",MAX_TRIES - tries);
        }
        if(correct_guesses == word_length)
        {
            printf("Congratulations.You have guessed the word:%s\n",word);
            break;
        }

    }
   if (correct_guesses != word_length)
{
    //displayHangman(tries);
    printf("GAME OVER! The word was: %s\n", word);
}
    return 0;
}
