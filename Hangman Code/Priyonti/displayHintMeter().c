void displayHintMeter(int maxHints, int usedHints) {
    printf(ORANGE "Hint Meter: " RESET);
    for (int i = 0; i < maxHints; i++) {
        if (i < usedHints) {
            printf(ORANGE "█" RESET);
        } else {
            printf(ORANGE "░" RESET);
        }
    }
    printf("\n");
}
