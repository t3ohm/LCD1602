#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <lcd1602.h>
#include <time.h>
#define blobit(x) #x
char* newline = blobit(\n);
int main(int argc, char* argv[])
{
    int rc;
    rc = lcd1602Init(1, 0x27);
    if (rc)
    {
        printf("Initialization failed; aborting...\n");
        return 0;
    }
    char* text = argv[1];
    char length[2];
    int commandaurgs = 1;
    int pairs = ((argc - commandaurgs) / 3);
    int pairbase;
    printf("XYtext pairs %d\n", pairs);
    lcd1602Control(1, 0, 0); // backlight on, underline off, blink block on
    //flipflop
    for (int i = 1; i < pairs + 1; ++i)
    {
        pairbase = (i - commandaurgs) * 3;
        int x = atoi(argv[pairbase + 1]);
        int y = atoi(argv[pairbase + 2]);
        char* text = argv[pairbase + 3];
        if (y == 3) {
            printf(text);
            printf(" for %d ms\n", x);
            usleep(x * 1000);
        }
        else {
            printf("lcdwrite( ");
            printf(text);
            printf(" ) @ Yrow: %d Xcol: %d ]\n", y, x);
            lcd1602SetCursor(x, y);
            lcd1602WriteString(text);
        }

    }
    for (int i = 1; i < pairs + 1; ++i)
    {
        pairbase = (i - commandaurgs) * 3;
        int x = atoi(argv[pairbase + 1]);
        int y = atoi(argv[pairbase + 2]);
        char* text = argv[pairbase + 3];
        int flipy;
        if (y == 3) {
            printf(text);
            printf(" for %d ms\n", x);
            usleep(x * 1000);
        }
        else {
            printf("lcdwrite( ");
            printf(text);
            if (y == 0) {
                flipy = 1;
            }
            else {
                flipy = 0;
            }
            printf(" ) @ Yrow: %d Xcol: %d ]\n", flipy, x);
            lcd1602SetCursor(x, flipy);
            lcd1602WriteString(text);
            lcd1602SetCursor(x, y);
            lcd1602WriteString(" ");
        }

    }
    return 0;
} /* main() */
