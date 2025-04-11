void main() {

    populateLevels();

    player();
    Sleep(800);
    system("cls");

    printf(CYAN "\n~~~~~~~~~~~~~~~~~~~~\n" RESET);
    printf(CYAN "~~~~~~~~~~~~~~~~~~~~\n" RESET);
    printf(LAVENDER " WELCOME TO HANGMAN\n" RESET);
    printf(CYAN "~~~~~~~~~~~~~~~~~~~~\n" RESET);
    printf(CYAN "~~~~~~~~~~~~~~~~~~~~\n" RESET);
    gameMenu();
    system("cls");

    
    while (levelCount <= MAX_LEVELS && gameCount <= MAX_GAMES) {
        tries = 0;
        correctGuessCount = 0;
        gameOver = false;
        hintTaken = false;
        memset(guessed, '\0', sizeof(guessed));

        printf(ROYAL_BLUE "\n-------LEVEL %d-------\n" RESET, levelCount);
        printf(PINK "-------GAME %d-------\n" RESET, gameCount);
        printf(PINK "\n----THEMES----\n" RESET);
        for (int i = 0; i < MAX_THEMES; i++) {
            printf("%d. %s\n", i+1, levels[levelCount-1].themes[i].name);
        }
        printf(BROWN "\nPress ESC to quit, or SPACE to go back to the Game Mode Menu.\n" RESET);
        printf(PURPLE "\nChoose a theme: " RESET);
        int key = _getch();
        if (key == 27) {
            int response = MessageBox(NULL,"Are you sure you want to quit?","Exit Confirmation",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
            
            if (response == IDYES) {
                system("cls");
                printf(DARK_PINK "\nLeaving the game\n" RESET);
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
        word = levels[levelCount-1].themes[themeChoice-1].words[wordIndex];

        time(&startTime);

        while (!gameOver) {
            system("cls");
            if (timeChallenge) {
                time(&currentTime);
                remainingTime = 60 - (int)difftime(currentTime, startTime);
                if (remainingTime <= 0) {
                    printf(RED BOLD "\nTIME'S UP!\n" RESET);
                    printf(RED BOLD "\nYOU LOSE!\n" RESET);
                    PlaySound("lose.wav", NULL, SND_FILENAME | SND_ASYNC);
                    displayHangman(MAX_TRIES);
                    wins = 0;
                    streakBroken = 1;
                    calculateScore();
                    saveProgress();
                    Sleep(3000);
                    system("cls");
                    break;
                }
                printf(YELLOW BOLD "\nTime Remaining: %d seconds\n" RESET, remainingTime);
            }
            calculateScore();
            if (hintTaken && hintCount <= 3) {
                printf(YELLOW "\nHint: %s\n\n" RESET,levels[levelCount-1].themes[themeChoice-1].hints[wordIndex]);
            }
            displayHangman(tries);

            for (int i = 0; i < strlen(word); i++) {
                if (word[i] == ' ') {
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
            for (int i = 0; i < strlen(word); i++) {
                if (toupper(word[i]) == toupper(guessedLetter)) {
                    guessed[i] = word[i];
                    found = true;
                    correctGuessCount++;
                }
            }

            if (!found) {
                system("cls");
                tries++;
                calculateScore();
                if (hintTaken && hintCount <= 3) {
                    printf(YELLOW "\nHint: %s\n\n" RESET,levels[levelCount-1].themes[themeChoice-1].hints[wordIndex]);
                }
                displayHangman(tries);
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
                Sleep(1200);
                system("cls");
            }
    
            if (tries == MAX_TRIES || correctGuessCount == strlen(word)) {
                gameOver = true;
                if (correctGuessCount == strlen(word)) {
                    system ("cls");
                    PlaySound("win.wav", NULL, SND_FILENAME | SND_ASYNC);
                    displayHangman(tries);
                    for (int i = 0; i < strlen(word); i++) {
                        printf("%c ", toupper(guessed[i]));
                    }
                    printf(GREEN BOLD "\n\nYOU WIN!\n" RESET);
                    gameCount++;
                    if (gameCount > MAX_GAMES) {
                        gameCount = 1;
                        levelCount++;
                        levelCompleted();
                    }
                    wins++;
                    if (wins > streak) {
                        streak = wins;
                    }
                    calculateScore();
                    saveProgress();
                    Sleep(3000);
                    system("cls");
                } else {
                    system("cls");
                    PlaySound("lose.wav", NULL, SND_FILENAME | SND_ASYNC);
                    displayHangman(tries);
                    printf(YELLOW "The word was: %s\n" RESET, word);
                    printf(RED BOLD "\n\nGAME OVER\n" RESET);
                    Sleep(1000);
                    printf(RED BOLD "\nYOU LOSE!\n" RESET);
                    wins = 0;
                    streakBroken = 1;
                    calculateScore();
                    saveProgress();
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
