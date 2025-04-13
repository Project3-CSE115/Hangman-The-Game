void display_Word(char *word, int level)
{
    clearScreen();
    int len = strlen(word);
    printf("Guess:");
    for (int i = 0; i < len; i++)
    {
        if (level >= 2 && i == 0)
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}
