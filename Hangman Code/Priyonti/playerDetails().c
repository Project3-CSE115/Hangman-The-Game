void playerDetails() {
    int tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3, age;
    char edit, newPlayerName[MAX_LENGTH], tempName[MAX_LENGTH];

    while (1) {
        printf(ROYAL_BLUE "\nPlayer Name: " RESET);
        printf("%s\n", player.name);
        printf(ORANGE "\nLongest Streak: " RESET);
        printf("%d\n", player.streak);
        printf(YELLOW "\nHighest Score: " RESET);
        printf("%d\n", player.highScore);
        printf(PINK "\nCurrent Level: " RESET);
        printf("%d\n", player.level);
        printf(GREEN "\nBadges Earned: \n" RESET);
        if (player.level >= 2) printf("%s\n", badges[0]);
        if (player.level >= 3) printf("%s\n", badges[1]);
        if (player.level >= 4) printf("%s\n", badges[2]);
        if (player.level >= 5) printf("%s\n", badges[3]);
        if (player.level >= 6) printf("%s\n", badges[4]);
        if (player.level == 6) printf("%s\n", badges[8]);
        if (player.hintBadge == 1) printf("%s\n", badges[5]);
        if (player.speedBadge == 1) printf("%s\n", badges[6]);
        if (player.streakBadge == 1) printf("%s\n", badges[7]);
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
            while (fscanf(file, "%s %d", tempName, &age) != EOF) {
                if (strcmp(tempName, player.name) == 0) {
                    fprintf(tempFile, "%s %d\n", newPlayerName, age);
                } else {
                    fprintf(tempFile, "%s %d\n", tempName, age);
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
            while (fscanf(file2, "%s %d %d %d %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken, &tempB1, &tempB2, &tempB3) != EOF) {
                if (strcmp(tempName, player.name) == 0) {
                    fprintf(tempFile2, "%s %d %d %d %d %d %d %d %d\n", newPlayerName, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3);
                } else {
                    fprintf(tempFile2, "%s %d %d %d %d %d %d %d %d\n", tempName, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3);
                }
            }
            fclose(file2);
            fclose(tempFile2);
            remove("stats.txt");
            rename("temp.txt","stats.txt");
            strcpy(player.name, newPlayerName);
            printf(GREEN "\nPlayer Name Updated Successfully!\n" RESET);
            Sleep(1000);
            system("cls");
        } else {
            break;
        }
    }
    printf(BROWN "\nPress any key to return to the Main Menu..." RESET);
    getchar();
    getchar();
    system("cls");
    gameMenu();
}
