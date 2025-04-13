
void leaderboard() {
    typedef struct {
        char name[MAX_LENGTH];
        int highScore;
    } PlayerStats;

    PlayerStats players[100];
    int playerCount = 0;

    FILE *file = fopen("stats.txt", "r");
    if (file == NULL) {
        printf(RED "\nError opening stats file!\n" RESET);
        return;
    }

    while (fscanf(file, "%s %*d %d %*d %*d %*d %*d %*d %*d", players[playerCount].name, &players[playerCount].highScore) != EOF) {
        playerCount++;
    }
    fclose(file);

    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = i + 1; j < playerCount; j++) {
            if (players[i].highScore < players[j].highScore) {
                PlayerStats temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf(CYAN BOLD "\n<-------LEADERBOARD------->\n" RESET);
    printf(YELLOW BOLD "\n%-5s %-20s %-10s\n" RESET, "Rank", "Player Name", "High Score");
    printf(YELLOW "-----------------------------------\n" RESET);

    for (int i = 0; i < playerCount && i < 10; i++) {
        printf(GREEN "%-5d %-20s %-10d\n" RESET, i + 1, players[i].name, players[i].highScore);
    }

    printf(BROWN "\nPress any key to return to the Main Menu..." RESET);
    getchar();
    getchar();
    system("cls");
}