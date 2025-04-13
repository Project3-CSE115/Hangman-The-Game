void levelCompleted() {
    printf(GREEN BOLD "\nCONGRATULATIONS! You have completed Level %d\n" RESET, levelCount);
    switch (levelCount) {
        case 1:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Rookie Rambler\"!\n" RESET);
            break;
        case 2:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Casual Challenger\"!\n" RESET);
            break;
        case 3:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Puzzle Pro\"!\n" RESET);
            break;
        case 4:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Mind Master\"!\n" RESET);
            break;
        case 5:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Hangman Hero\"!\n" RESET);
            break;
        default:
            printf(ROYAL_BLUE BOLD "\nYou have now officially mastered this game!\n GOODBYE :)\n" RESET);
            exit(0);
    }
}
