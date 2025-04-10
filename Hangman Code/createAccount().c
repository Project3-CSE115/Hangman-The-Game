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

    FILE *file1 = fopen("players.txt","a");
    fprintf(file1, "%s\n", playerName);
    fclose(file1);
    printf(GREEN "\nAccount Created Successfully!\n" RESET);
}
