# Hangman Game

Welcome to the **Hangman Game**, a feature-rich word-guessing game implemented in C. This program offers multiple game modes, player profiles, badges, and a leaderboard system to provide an engaging and interactive experience.

---

## Features

### 1. **Game Modes**
- **Normal Mode**: Play through levels with increasing difficulty.
- **Time Challenge Mode**: Guess the word within 2 minutes per game.
- **Time Attack Mode**: Guess as many words as possible within 5 minutes.
- **Multiplayer Mode**: Two players take turns setting and guessing words.

### 2. **Player Profiles**
- Create and log in to player accounts.
- Track progress, including streaks, high scores, and badges.
- Update player names and view detailed profiles.

### 3. **Badges**
Earn badges for completing specific challenges:
- **Rookie Rambler**: Complete Level 1.
- **Casual Challenger**: Complete Level 2.
- **Puzzle Pro**: Complete Level 3.
- **Mind Master**: Complete Level 4.
- **Hangman Hero**: Complete Level 5.
- **Hintless Hero**: Complete a level without using hints.
- **Speed Guesser**: Complete a game in Time Challenge Mode with more than 60 seconds remaining.
- **Streak Master**: Achieve a streak of 5 or more wins.
- **Time Warrior**: Score 100+ points or guess 10+ words in Time Attack Mode.
- **Ultimate Champion**: Master all levels.

### 4. **Leaderboard**
- View the top 10 players based on high scores.

### 5. **Hints**
- Use hints to help guess the word (limited to 3 hints per session).

### 6. **Animations and Sound Effects**
- Victory and loss animations.
- Sound effects for wins, losses, and other events.

---

## How to Play

### 1. **Main Menu**
- Choose to create an account, log in, or play as a guest.
- Access game modes, instructions, leaderboard, and credits.

### 2. **Gameplay**
- Guess letters to complete the word before running out of tries.
- Each correct guess earns points, while incorrect guesses reduce your score.
- Use hints strategically to avoid losing points.

### 3. **Game Modes**
- **Normal Mode**: Progress through levels and themes.
- **Time Challenge Mode**: Guess the word within 2 minutes.
- **Time Attack Mode**: Choose a theme and guess as many words as possible in 5 minutes.
- **Multiplayer Mode**: Take turns setting and guessing words with another player.

---

## Scoring System

- **+5 points** for each correct guess.
- **-1 point** for each incorrect guess.
- **-3 points** for using a hint.

---

## File Structure

- **players.txt**: Stores player names and ages.
- **stats.txt**: Stores player statistics, including streaks, high scores, and badges.
- **temp.txt**: Temporary file used for updating player data.

---

## Requirements

- **Operating System**: Windows
- **Compiler**: GCC or any C compiler supporting `windows.h` and `mmsystem.h`.

---

## How to Run

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your-username/hangman-game.git
   cd hangman-game
2. **Compile the program:** *gcc Hangman.c -o Hangman.exe -lwinmm*
3. **Run the program:** *./Hangman.exe*

---

## Challenges Faced

- **File Handling**: Managing player data across sessions required robust file handling to ensure data integrity.
- **Real-Time Timer**: Implementing countdown timers for Time Challenge and Time Attack modes while maintaining smooth gameplay.
- **Dynamic Memory Management**: Allocating and freeing memory for themes, words, and hints without leaks.
- **Cross-Platform Compatibility**: The use of Windows-specific libraries limits portability.

---

## Future Improvements

- **Cross-Platform Support**: Adapt the program for Linux and macOS.
- **Enhanced UI**: Add a graphical user interface (GUI) for better user experience.
- **Additional Game Modes**: Introduce new modes, such as cooperative or competitive multiplayer.
- **Custom Themes**: Allow players to create and share custom themes.

---

## Credits
- Priyonti Tabassum Haque
- Sumaiya Yasmin Nairit
- Dizzya Al Fahad
- Avishek Saha
