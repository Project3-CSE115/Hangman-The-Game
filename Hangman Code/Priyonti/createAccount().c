void createAccount() {
    char playerName[MAX_LENGTH], dob[11];

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
    printf(PURPLE "\nEnter date of birth(DD/MM/YYYY): " RESET);
    scanf("%s", dob);
    while (!isDobValid(dob)) {
        printf(RED "\nInalid dob format.\n" RESET);
        printf(PURPLE "\nEnter date of birth(DD/MM/YYYY): " RESET);
        scanf("%s", dob);
    }
    strcpy(player.name, playerName);
    FILE *file1 = fopen("players.txt","a");
    if (file1 == NULL) {
        printf(RED "\nError opening this file!\n" RESET);
        return;
    }
    fprintf(file1, "%s %d\n", player.name, player.age);
    fclose(file1);
    FILE *file2 = fopen("stats.txt","a");
    if (file2 == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }
    fprintf(file2, "%s %d %d %d %d %d %d %d %d\n", player.name, player.streak, player.highScore, 1, 1, 0, 0, 0, 0);
    fclose(file2);
    printf(GREEN "\nAccount Created Successfully!\n" RESET);
}
