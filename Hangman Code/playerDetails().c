void playerDetails() {
    int tempStreak, tempScore, tempLevel, tempGame, tempBroken;
    char edit, newPlayerName[MAX_LENGTH], tempName[MAX_LENGTH];

    printf(ROYAL_BLUE "\nPlayer Name: " RESET);
    printf("%s\n", currentPlayer);
    printf(ORANGE "\nLongest Streak: " RESET);
    printf("%d\n", streak);
    printf(YELLOW "\nHighest Score: " RESET);
    printf("%d\n", highestScore);
    printf(PINK "\nCurrent Level: " RESET);
    printf("%d\n", levelCount);
    printf(PURPLE "\nWant to edit player name?(y/n): " RESET);
    scanf(" %c", &edit);
    while (tolower(edit) != 'y' && tolower(edit) != 'n') {
        printf(RED "\nInvalid input. Enter 'y' or 'n'.\n" RESET);
        printf(PURPLE "\nWant to edit player name?(y/n): " RESET);
        scanf(" %c", &edit);
    }
    if (tolower(edit) == 'y') {
        system("cls");
        printf(PURPLE "\nEnter new player name: " RESET);
        scanf("%s", newPlayerName);
        while (nameTaken(newPlayerName) || !nameValid(newPlayerName)) {
            if (nameTaken(newPlayerName)) {
                printf(RED "\nThis player name is already taken.\n" RESET);
            } else {
                printf(RED "\nThe player name should be less than 20 characters.\n" RESET);
            }
            printf(PURPLE "\nEnter new player name: " RESET);
            scanf("%s", newPlayerName);
        }
        FILE *file = fopen("players.txt","r");
        FILE *tempFile = fopen("temp.txt","w");
        if (file == NULL || tempFile == NULL) {
            printf(RED "\nError opening file!\n" RESET);
            return;
        }
        while (fscanf(file, "%s", tempName) != EOF) {
            if (strcmp(tempName, currentPlayer) == 0) {
                fprintf(tempFile, "%s\n", newPlayerName);
            } else {
                fprintf(tempFile, "%s\n", tempName);
            }
        }
        fclose(file);
        fclose(tempFile);
        if (remove("players.txt") != 0) {
            printf(RED "\nError deleting players.txt!\n" RESET);
        }
        if (rename("temp.txt", "players.txt") != 0) {
            printf(RED "\nError renaming temp.txt to players.txt!\n" RESET);
        }

        FILE *file2 = fopen("stats.txt","r");
        FILE *tempFile2 = fopen("temp.txt","w");
        if (file2 == NULL || tempFile2 == NULL) {
            printf(RED "\nError opening file!\n" RESET);
            return;
        }
        while (fscanf(file2, "%s %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken) != EOF) {
            if (strcmp(tempName, currentPlayer) == 0) {
                fprintf(tempFile2, "%s %d %d %d %d %d\n", newPlayerName, tempStreak, tempScore, tempLevel, tempGame, tempBroken);
            } else {
                fprintf(tempFile2, "%s %d %d %d %d %d\n", tempName, tempStreak, tempScore, tempLevel, tempGame, tempBroken);
            }
        }
        strcpy(currentPlayer, newPlayerName);
        fclose(file2);
        fclose(tempFile2);
        remove("stats.txt");
        rename("temp.txt","stats.txt");
        strcpy(currentPlayer, newPlayerName);
        printf(GREEN "\nPlayer Name Updated Successfully!\n" RESET);
        Sleep(1000);
        system("cls");
        playerDetails();
    }
    printf(BROWN "\nPress any key to return to the Main Menu..." RESET);
    getchar();
    getchar();
    system("cls");
    gameMenu();
}
