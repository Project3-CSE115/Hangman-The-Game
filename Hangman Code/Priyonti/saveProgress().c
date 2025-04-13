void saveProgress() {
    char tempName[MAX_LENGTH];
    int tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3;

    FILE *file = fopen("stats.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf(RED "\nError opening file!\n" RESET);
        return;
    }

    while (fscanf(file, "%s %d %d %d %d %d %d %d %d", tempName, &tempStreak, &tempScore, &tempLevel, &tempGame, &tempBroken, &tempB1, &tempB2, &tempB3) != EOF) {
        if (strcmp(tempName, player.name) == 0) {
            fprintf(tempFile, "%s %d %d %d %d %d %d %d %d\n", player.name, player.streak, player.highScore, player.level, player.game, player.streakBroken, player.hintBadge, player.speedBadge, player.streakBadge);
        } else {
            fprintf(tempFile, "%s %d %d %d %d %d %d %d %d\n", tempName, tempStreak, tempScore, tempLevel, tempGame, tempBroken, tempB1, tempB2, tempB3);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("stats.txt");
    rename("temp.txt", "stats.txt");
}
