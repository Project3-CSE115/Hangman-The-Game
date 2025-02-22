int main ()
{
    displaytitle();

    printf("Welcome to the HANGMAN game!\n");
    getchar();

    printf("Your task is to guess the word before the stickman is fully hanged.\n");
    getchar();

    printf("Maximum wrong guesses: 6\n");
    getchar();

    printf("Good Luck!");
    getchar();

    srand(time(0));

    const char *word = wordList[rand() % WORD_COUNT];
    int word_length = strlen(word);
    int guessed[word_length];
    memset(guessed, 0, sizeof(guessed));
    int tries = 0;
    int correct_guesses = 0;
    char guess;
}
