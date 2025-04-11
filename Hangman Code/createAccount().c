void createAccount() {
    char playerName[MAX_LENGTH];

    printf(PURPLE "\nEnter player name: " RESET);
    scanf("%s", playerName);
    while (nameTaken(playerName) || !nameValid(playerName)) {
        if (nameTaken(playerName)) {
            printf(RED "\nThis player name is already taken.\n" RESET);
        } else {
            printf(RED "\nThe player name should be less than 20 characters.\n" RESET);
        }
        printf(PURPLE "\nEnter player name: " RESET);
        scanf("%s", playerName);
    }
    strcpy(currentPlayer, playerName);
    FILE *file1 = fopen("players.txt","a");
    if (file1 == NULL) {
        printf(RED "\nError opening this file!\n" RESET);
        return;
    }
    fprintf(file1, "%s\n", playerName);
    fclose(file1);
    FILE *file2 = fopen("stats.txt","a");
    if (file2 == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }
    fprintf(file1, "%s %d %d %d %d %d\n", playerName, streak, highestScore, 1, gameCount, streakBroken);
    fclose(file2);
    printf(GREEN "\nAccount Created Successfully!\n" RESET);
}
