void player() {
    int choice;
    bool playerFound = false;
    char playerName[MAX_LENGTH], tempPlayer[MAX_LENGTH], redirect;

    system("cls");
    printf(CYAN BOLD "\nWelcome to HANGMAN\n" RESET);
    printf(CREAM "\n1. Create account\n" RESET);
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
                    Sleep(1000);
                    system("cls");
                    printf(PURPLE "\nEnter player name: " RESET);
                    scanf("%s", playerName);
                }
                
                FILE *file = fopen("players.txt","r");
                while (fscanf(file, "%s", tempPlayer) != EOF) {
                    if (strcmp(playerName, tempPlayer) == 0) {
                        printf(GREEN "\nLog In Successful!\n" RESET);
                        playerFound = true;
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
                fclose(file);
            } while (tolower(redirect) == 'n');
            break;
        case 3:
            isGuest = true;
            return;
        default:
            printf(RED "\nInvalid choice. Enter one of the options on screen.\n" RESET);
    }
}
