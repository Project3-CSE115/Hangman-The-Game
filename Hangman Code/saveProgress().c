void saveProgress() {
    char tempName[MAX_LENGTH];
    int tempStreak, tempScore, tempLevel, tempGame, tempBroken;

    FILE *file = fopen("stats.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    printf(GREEN "\nSaving progress for player: %s\n" RESET, currentPlayer);
    printf(GREEN "Streak: %d, Highest Score: %d, Level: %d, Game: %d, Streak Broken: %d\n" RESET,
           streak, highestScore, levelCount, gameCount, streakBroken);

    while (fscanf(file, "%s %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken) != EOF) {
        if (strcmp(tempName, currentPlayer) == 0) {
            fprintf(tempFile, "%s %d %d %d %d %d\n", currentPlayer, streak, highestScore, levelCount, gameCount, streakBroken);
        } else {
            fprintf(tempFile, "%s %d %d %d %d %d\n", tempName, tempStreak, tempScore, tempLevel, tempGame, tempBroken);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("stats.txt");
    rename("temp.txt", "stats.txt");
}
