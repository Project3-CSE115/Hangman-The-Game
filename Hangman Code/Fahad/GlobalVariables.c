int gameCount = 1, remainingTime, tries = 0, correctGuessCount = 0, themeChoice, wordIndex, hintCount = 0, streak = 0, highestScore = 0, wins = 0, streakBroken = 0;
bool hintTaken, gameOver, isGuest = false, timeChallenge = false, revealLetter = false;
const char *word;
char guessedLetter, guessed[MAX_LENGTH], currentPlayer[MAX_LENGTH];
time_t startTime, currentTime;
