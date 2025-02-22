void displayWord(const char *word, const int*guessed)

for(int i = 0; i < strlen(word); i++)

 if (guessed[i])

printf("%c", word[i]);

else

 printf("_ ");
