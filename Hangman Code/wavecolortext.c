#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
    #define SLEEP(ms) Sleep(ms)
#else
    #define SLEEP(ms) usleep((ms) * 1000)
#endif

#define DELAY 115
#define BDELAY 50
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define GREEN "\033[0;32m"
#define CYAN "\033[1;36m"
#define MAGENTA "\033[1;35m"
#define BOLD_YELLOW "\033[1;33m"
#define YELLOW "\033[0;33m"
#define RED "\033[0;31m"
#define ORANGE "\033[38;2;255;140;0m"
#define LAVENDER "\033[38;5;183m"
#define BROWN "\033[38;2;139;69;19m"
#define PINK "\033[38;2;255;192;203m"
#define DARK_PINK "\033[38;2;231;84;128m"
#define PURPLE "\033[1;35m"
#define ROYAL_BLUE "\033[0;34m"
#define CREAM "\033[38;2;255;253;208m"
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"




void waveText(const char *text, const char *color1, const char *color2) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (i % 2 == 0)
            printf("%s%c" RESET, color1, text[i]);
        else
            printf("%s%c" RESET, color2, text[i]);
        fflush(stdout);
        Sleep(DELAY);
    }
    printf("\n");
}
