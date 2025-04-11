void calculateScore() {
    int score = 0;
    score += (5*correctGuessCount);
    score -= (1*tries);
    if (hintTaken) {
        score-=3;
    }
    printf(CREAM BOLD "\n\nYour score: %d\n\n" RESET, score);

    if (score > highestScore) {
        highestScore = score;
    }
}
