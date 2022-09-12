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
    int exe = 1;
    int commandaurgs = exe + 1;
    int rc;
    rc = lcd1602Init(1, 0x27);
    if (rc)
    {
        printf("Initialization failed; aborting...\n");
        return 0;
    }
    int pairs = ((argc - commandaurgs) / 3);
    int pairbase;
    int x;
    int y;
    int sleeptime = atoi(argv[1]) * 1000;
    printf("XYtext pairs %d\n", pairs);
    printf("usleep set to  %d ms\n", atoi(argv[1]));
    lcd1602Control(1, 0, 1); // backlight on, underline off, blink block on
    for (int i = 1; i < pairs + 1; ++i)
    {
        pairbase = (i - 1) * 3;
        x = atoi(argv[pairbase + commandaurgs]);
        y = atoi(argv[pairbase + commandaurgs + 1]);
        char* text = argv[pairbase + commandaurgs + 2];
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
            usleep(sleeptime);
        }
    }
    return 0;
} /* main() */
