

while (tries < MAX_TRIES)  // Loop runs until the maximum number of tries is reached
{
    displayHangman(tries);  // Displays the current state of the hangman

    displayWord(word, guessed);  // Displays the word with guessed letters revealed

    printf("Enter Your Guess: ");  // Prompts the user to enter a guess
    scanf(" %c", &guess);  // Reads a character input from the user
                           // The space before %c helps ignore newline characters

    guess = toupper(guess);  // Converts the input character to uppercase for consistency

    int found = 0;  // Variable to track if the guessed letter is found in the word
}
