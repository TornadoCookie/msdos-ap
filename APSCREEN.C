#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "WAV.H"

enum Pairs {
    RESERVED_PAIR,
    HEADER_PAIR
};

//Print slow
void prints(const char *fmt) {
    for (int i = 0; i < strlen(fmt); i++) {
        char current = fmt[i];
        printw("%c", current);
        refresh();
        usleep(10000);
    }
}

int main() {
    //Clear up any other instances of ACTIVATION.COM
#ifdef __linux__
    system("killall -w ACTIVATION.COM");
#elif defined(_WIN32)
    system("taskkill /F /IM ACTIVATION.COM /T");
#endif
    initscr();
    noecho();
    clear();
    if (!has_colors()) {
        endwin();
        printf("NO COLORS\n");
        exit(1); 
    }
    start_color();
    init_pair(HEADER_PAIR, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(HEADER_PAIR));
    curs_set(0);
    playSoundInNewThread("Windows XP Installation Theme (8-Bit) [AdUBXuNczvQ].wav", 323);
    printw("                                                                                   \n"
           "                Microsoft MS-DOS 6.22 ANTI-PIRACY TOOL                             \n");
    attroff(COLOR_PAIR(HEADER_PAIR));
    printw("===================================================================================\n");
    prints("                                                                                   \n"
           "  It is illegal to pirate, or otherwise steal used software from Microsoft.        \n"
           "  Your computer has been locked due to this felony that was performed.             \n"
           "                                                                                   \n"
           "  If you feel this is a mistake, please call the official MS Anti-Piracy hotline   \n"
           "  at (800) (785-3448).                                                             \n"
           "                                                                                   \n"
           "  Your local department has been notified of this action, and you may face         \n"
           "  possible legal action against you.                                               \n"
           "                                                                                   \n"
           "  This varies from state by state. In the US, you may get a fine of up to $250.000 \n"
           "  dollars.                                                                         \n"
           "                                                                                   \n"
           "  Piracy is a serious crime. Do not attempt to do this again.                      \n"
           "                                                                                   \n"
           "  Thank you for choosing microsoft.                                                \n"
           "                                                                                   \n"
           "  PRESS F1 TO OPEN DIALER                                                          \n"
           "  PRESS ANY OTHER KEY TO SHUT DOWN YOUR COMPUTER                                   \n");
    while (1) {
        int c = getch();
        if (c == KEY_F(1)) {

        } else {
            endwin();
            stopSound();
            clear();
            return 0;
        }
    }
    endwin();
    stopSound();
    clear();
    return 0;
}