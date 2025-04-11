void playerDetails() {
    char edit, newPlayerName[MAX_LENGTH], tempName[MAX_LENGTH];

    printf(ROYAL_BLUE "\nPlayer name: %s\n" RESET, currentPlayer);
    printf(PURPLE "\nWant to edit(y/n): " RESET);
    scanf(" %c", &edit);
    while (tolower(edit) != 'y' && tolower(edit) != 'n') {
        printf(RED "\nInvalid input. Enter 'y' or 'n'.\n" RESET);
        printf(PURPLE "\nWant to edit?(y/n): " RESET);
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
        while (fscanf(file, "%s\n", tempName) != EOF) {
            if (strcmp(tempName, currentPlayer) == 0) {
                fprintf(tempFile, "%s\n", newPlayerName);
            } else {
                fprintf(tempFile, "%s\n", tempName);
            }
        }
        strcpy(currentPlayer, newPlayerName);
        fclose(file);
        fclose(tempFile);
        remove("players.txt");
        rename("temp.txt","players.txt");
        printf(GREEN "\nPlayer Name Updated Successfully!\n" RESET);
        Sleep(1000);
        system("cls");
    }
    
}
