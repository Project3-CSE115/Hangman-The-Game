const char *badges[MAX_BADGES] = {"Rookie Rambler","Casual Challenger","Puzzle Pro","Mind Master",
    "Hangman Hero","Hintless Hero","Speed Guesser","Streak Master","Ultimate Champion"};

void awardBadge(int badgeIndex) {
    if (badgeIndex < 0 || badgeIndex >= MAX_BADGES) {
        return;
    }
    printf(ROYAL_BLUE "\nCongratulations! You have earned the" RESET);
    printf("\"%s\"", badges[badgeIndex]);
    printf(ROYAL_BLUE "badge.\n" RESET);
    Sleep(2000);
}

void levelCompleted() {
    printf(GREEN BOLD "\nCONGRATULATIONS! You have completed Level %d\n" RESET, levelCount);
    switch (levelCount) {
        case 1:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Rookie Rambler\"!\n" RESET);
            awardBadge(0);
            break;
        case 2:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Casual Challenger\"!\n" RESET);
            awardBadge(1);
            break;
        case 3:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Puzzle Pro\"!\n" RESET);
            awardBadge(2);
            break;
        case 4:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Mind Master\"!\n" RESET);
            awardBadge(3);
            break;
        case 5:
            printf(ROYAL_BLUE BOLD "\nYou now qualify as a \"Hangman Hero\"!\n" RESET);
            awardBadge(4);
            break;
        default:
            printf(ROYAL_BLUE BOLD "\nYou have now officially mastered this game!\n GOODBYE :)\n" RESET);
            awardBadge(9);
    }
}
