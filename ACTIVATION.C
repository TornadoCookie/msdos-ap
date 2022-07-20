#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

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
    #ifdef _WIN32
    puts("ERROR: NO ACTIVATION ID FOUND");
    #endif
    initscr();
    clear();
    noecho();
    curs_set(0);
    printw("Starting MS-DOS...\n\n");
    refresh();
    sleep(1);
    printw("HIMEM is testing extended memory...\n\n");
    refresh();
    sleep(1);
    printw("C:\\>DOS\\AP\\ACTIVATION.COM\n");
    prints("LOADING, PLEASE DO NOT SHUT DOWN YOUR COMPUTER");
    refresh();
    for (int i = 0; i < 999; i++) {
        usleep(10000);
        printw(".");
        refresh();
    }
    prints("\nINITIALIZATION COMPLETE.\n");
    prints("NOW OPENING \\APSCREEN.exe\n");
    refresh();
    sleep(1);
    endwin();
    system("DOS/AP/APSCREEN.exe");
    return 0;
}