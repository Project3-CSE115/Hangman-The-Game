typedef struct {
    char name[MAX_LENGTH];
    int age;
    int streak;
    int highScore;
    int level;
    int game;
    int streakBroken;
    int hintBadge;
    int speedBadge;
    int streakBadge;
} Player;

Player player;

void playerMenu() {
    int choice, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, age;
    bool playerFound = false;
    char playerName[MAX_LENGTH], tempName[MAX_LENGTH], redirect;

    system("cls");
    printf(CYAN BOLD "\nWelcome to HANGMAN\n" RESET);
    printf(CREAM "\n1. Create Account\n" RESET);
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
                    printf(PURPLE "\nEnter player name: " RESET);
                    scanf("%s", playerName);
                }
                
                FILE *file1 = fopen("stats.txt","r");
                if (file1 == NULL) {
                    printf(RED "\nError opening file!\n" RESET);
                    return;
                }
                while (fscanf(file1, "%s %d %d %d %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken, &tempB1, &tempB2, &tempB3) != EOF) {
                    if (strcmp(tempName, playerName) == 0) {
                        strcpy(player.name, playerName);
                        player.streak = tempStreak;
                        player.highScore = tempScore;
                        player.level = tempLevel;
                        player.game = tempGame;
                        player.streakBroken = tempBroken;
                        if (player.streakBroken == 0) {
                            wins = player.streak;
                        }
                        player.hintBadge = tempB1;
                        player.speedBadge = tempB2;
                        player.streakBadge = tempB3;
                        break;
                    }
                }
                fclose(file1);

                FILE *file = fopen("players.txt","r");
                if (file == NULL) {
                    printf(RED "\nError opening file!\n" RESET);
                    return;
                }
                while (fscanf(file, "%s %d", tempName, &age) != EOF) {
                    if (strcmp(playerName, tempName) == 0) {
                        printf(GREEN "\nLog In Successful!\n" RESET);
                        player.age = age;
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
