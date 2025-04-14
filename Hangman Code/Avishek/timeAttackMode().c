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