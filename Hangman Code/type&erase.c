#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define DELAY 150000
#define RESET "\033[0m"
#define HGRN "\e[0;92m"

void typeAndErase(const char *message)
{
    int len = strlen(message);
     for (int i = 0; i < len; i++)
     {
         printf(HGRN "%c" RESET, message[i]);
         fflush(stdout);
         usleep(DELAY);
     }

     usleep(5000000);

     for (int i = len-1; i >= 0; i--)
     {
         printf("\b \b");
         fflush(stdout);
         usleep(DELAY);

     }
}
