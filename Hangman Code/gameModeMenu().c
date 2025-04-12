void gameModeMenu() {
    int modeChoice;

    printf(LAVENDER "\n<-------GAME MODE MENU------->\n" RESET);
    printf(GREEN "1. Normal Mode\n" RESET);
    printf(YELLOW "2. Time Challenge Mode\n" RESET);
    printf(PINK "3. Multiplayer Mode\n" RESET);
    printf(ORANGE "4. Go Back\n" RESET);
    printf(PURPLE "Choose an option: " RESET);

    while (scanf("%d", &modeChoice) != 1) {
        printf(RED "\nInvalid input! Please enter a number.\n" RESET);
        while (getchar() != '\n');
        printf(PURPLE "\nChoose an option: " RESET);
    }

    switch (modeChoice) {
        case 1:
            printf(GREEN "\nYou have chosen Normal Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            return;
        case 2:
            printf(YELLOW "\nYou have chosen Time Challenge Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            timeChallengeMode();
            break;
        case 3:
            printf(PINK "\nYou have chosen Multiplayer Mode.\n" RESET);
            Sleep(1000);
            system("cls");
            multiplayerMode();
            break;
        case 4:
            system("cls");
            gameMenu();
            break;
        default:
            printf(RED "\nInvalid choice. Please select a valid game mode.\n" RESET);
            Sleep(1000);
            system("cls");
            gameModeMenu();
            break;
    }
}
