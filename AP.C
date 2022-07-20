#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "OGG.H"

#ifdef _WIN32
#define cmd_clear "CLS"
#elif defined(__linux__)
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#define cmd_clear "clear"
#endif


wchar_t *repeatStr (const wchar_t *str, size_t count) {
    if (count == 0) return L"";
    wchar_t *ret = (wchar_t*)malloc(wcslen(str) * WCHAR_WIDTH * count + count);
    if (ret == NULL) return NULL;
    wcscpy (ret, str);
    while (--count > 0) {
        ret = wcscat (ret, str);
    }
    return ret;
}


int process_main_input = TRUE;
int process_licensekey_input = TRUE;

bool can_restart = true;

void restart() {
    if (!can_restart) return;
    can_restart = false;
    refresh();
    clear();
    endwin();
    system("DOS/AP/ACTIVATION.COM");
}

void *waitForEnter(void *t) {
    while (can_restart) {
        int c = getch();
        if (c == KEY_ENTER || c == '\n') restart();
    }
}

//Print slow
void prints(const char *fmt) {
    for (int i = 0; i < strlen(fmt); i++) {
        char current = fmt[i];
        printw("%c", current);
        refresh();
        usleep(1000);
    }
}

void setFooterText(const char *msg) {
    attron(A_STANDOUT);
    mvprintw(21, 0, "%s", msg);
    attroff(A_STANDOUT);
}

#define OPTION_OFFSET 6
enum Pairs {
    RESERVED_PAIR,
    LICENSEKEY_BACKGROUND,
    LICENSEKEY_BACKGROUND_ENTER,
    FLOPPY_ACTIVATION
};

void employee() {

}

void license_activation() {
    process_licensekey_input = FALSE;
    clear();
    setFooterText(" F1=Help                                                                         ");
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0, 0);
    printw("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0, 0);
    printw("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n");
    printw("     Welcome to the license key activation.                                       \n");
    usleep(500000);
    refresh();
    printw("                                                                                  \n");
    printw("     Please restart the computer if you have pressed the wrong                    \n"); //44-45
    usleep(500000);
    refresh();
    printw("     button.                                                                      \n");
    usleep(500000);
    refresh();
    printw("                                                                                  \n");
    printw("     Please grab your MS-DOS installation floppy disk. Click a                    \n");
    usleep(500000);
    refresh();            
    printw("     number.                                                                      \n");
    usleep(500000);
    refresh();
    printw("                                                                                  \n");
    printw("     Which type of installation diskette do you have?                             \n");
    usleep(500000);
    refresh();
    printw("                                                                                  \n");
    printw("     1. IBM-branded MS-DOS floppy disk                                            \n");
    usleep(500000);
    refresh();
    printw("     2. Back-up MS-DOS floppy disk                                                \n");
    usleep(500000);
    refresh();
    printw("     3. Supplemential floppy disk                                                 \n");
    usleep(500000);
    refresh();
    printw("     4. MS-DOS floppy disk                                                        \n");
    usleep(500000);
    refresh();
    printw("     5. Show more options                                                         \n");
    usleep(500000);
    refresh();
    printw("                                                                                  \n");
    printw("                                                                                  \n");
    printw("                                                                                  \n");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    refresh();
    while (1) {
        int c = getch();
        if (c == '1' || c == '2' || c == '3' || c == '4') break;
    }
    attron(A_STANDOUT);
    mvaddwstr(7, 15, L"┌─────────────────────────────────────────────┐");
    mvaddwstr(8, 15, L"│             License key activation          │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(9, 15, L"│                                             │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(10, 15, L"│            Press any key to type            │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(11, 15, L"│                                             │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(12, 15, L"│                                             │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(13, 15, L"└─────────────────────────────────────────────┘");
    attroff(A_STANDOUT);
    printw("  ");
    mvprintw(14, 15, "                                                 ");
    attron(A_STANDOUT);
    char input[21] = "";
    setFooterText(" F1=Help     F2= Show visual example                                             ");
    move(10, 28);
    noecho();
    int visualExampleOpen = FALSE;
    int firstKeyCode = TRUE;
    while (1) {
        int c = getch();
        if (c == 8 || c == KEY_BACKSPACE) {
            input[strlen(input)] = '\0';
            attron(A_STANDOUT);
            noecho();
        } else if ((isprint(c) || c == ' ') && strlen(input) != 21) {
            if (firstKeyCode) {
                setFooterText(" F1=Help     ENTER = Verify license key                                          ");
                attron(A_STANDOUT);
                move(10, 28);
                firstKeyCode = FALSE;
            }
            input[strlen(input)] = c;
            input[strlen(input)+1] = '\0';
            mvprintw(10, 28, "%-21s", input);
        } else if (c == KEY_ENTER || c == '\n') {
            break;
        } else if (strlen(input) == 20) {
            noecho();
        } else if (c == KEY_F(2) && visualExampleOpen == FALSE && input[0] == '\0') {
            visualExampleOpen = TRUE;
            setFooterText(" F1=Help     F2= Hide visual example                                             ");
            attroff(A_STANDOUT);
            mvprintw(3, 0, 
                    "                                                                                  \n"
                    "                                                                                  \n"
                    "      Floppy disk example                                                         \n"
                    "                                                                                  \n"
                    "      -----------------                                                           \n"
                    "      |     |MICROSOFT|                                                           \n"
                    "      |     |???-?????|  <---                                                     \n"
                    "      |     |---------|                                                           \n"
                    "      |---------------|                                                           \n"
                    "                                                                                  \n");
        } else if (c == KEY_F(2) && visualExampleOpen == TRUE) {
            attroff(A_STANDOUT);
            visualExampleOpen = FALSE;
            clear();
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0, 0);
    printw("                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0, 0);
    prints("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "     Welcome to the license key activation.                                       \n"
           "                                                                                  \n"
           "     Please restart the computer if you have pressed the wrong                    \n" //44-45
           "     button.                                                                      \n"
           "                                                                                  \n"
           "     Please grab your MS-DOS installation floppy disk. Click a                    \n"            
           "     number.                                                                      \n"
           "                                                                                  \n"
           "     Which type of installation diskette do you have?                             \n"
           "                                                                                  \n"
           "     1. IBM-branded MS-DOS floppy disk                                            \n"
           "     2. Back-up MS-DOS floppy disk                                                \n"
           "     3. Supplemential floppy disk                                                 \n"
           "     4. MS-DOS floppy disk                                                        \n"
           "     5. Show more options                                                         \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
           attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(A_STANDOUT);
    printw(" F1=Help     F2= Show visual example                                             ");
    attroff(A_STANDOUT);
    refresh();
    attron(A_STANDOUT);
    mvaddwstr(7, 15, L"┌─────────────────────────────────────────────┐");
    mvaddwstr(8, 15, L"│             License key activation          │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(9, 15, L"│                                             │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(10, 15, L"│            Press any key to type            │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(11, 15, L"│                                             │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(12, 15, L"│                                             │");
    attroff(A_STANDOUT);
    printw("  ");
    attron(A_STANDOUT);
    mvaddwstr(13, 15, L"└─────────────────────────────────────────────┘");
    attroff(A_STANDOUT);
    printw("  ");
    mvprintw(14, 15, "                                                 ");
    move(10, 28);
    attron(A_STANDOUT);
        } 
    }
    init_pair(FLOPPY_ACTIVATION, COLOR_RED, COLOR_BLUE);
    attroff(A_STANDOUT);
    setFooterText(" F1=Help     F2 = Skip                                                            ");
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0,0);
        printw("                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0,0);
    printw("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "     Thank you for typing out your license key.                                   \n"
           "     The computer must perform a multitude of steps to verify                     \n"
           "     the license key is valid.                                                    \n"
           "                                                                                  \n"
           "     Please look below.                                                           \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "     -> ");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(COLOR_PAIR(FLOPPY_ACTIVATION));
    printw("FLOPPY DISK ACTIVATION");
    attroff(COLOR_PAIR(FLOPPY_ACTIVATION));
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    printw("                                                    \n"
           "                                                                                  \n"
           "     - VERIFY WITH INTERNET CONNECTION                                            \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "     CURRENT_PROGRESS: NOT INSERTED                                               \n"
           "     FLOPPY DRIVE COMPATIBILITY: YES                                              \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(A_STANDOUT);
    refresh();
    sleep(3);
    mvprintw(21, 0, " Verifying floppy disk...                                                         ");
    attroff(A_STANDOUT); 
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    mvprintw(15, 0, "     CURRENT_PROGRESS: INSERTED                                                   \n");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(A_STANDOUT);
    refresh();
    mvaddwstr(7, 15, L"┌────────────────────────────────────────────┐");
    mvaddwstr(8, 15, L"│        Floppy disk verification            │");
    mvaddwstr(9, 15, L"│                                            │");
    mvaddwstr(10, 15,L"│                                            │");
    mvaddwstr(11, 15,L"│  ----------------------------------------  │");
    mvaddwstr(12, 15,L"│                                            │");
    mvaddwstr(13, 15,L"│                                            │");
    mvaddwstr(14, 15,L"└────────────────────────────────────────────┘");
    refresh();
    attroff(A_STANDOUT);
    mvprintw(8, 61, "  ");
    mvprintw(9, 61, "  ");
    mvprintw(10, 61, "  ");
    mvprintw(11, 61, "  ");
    mvprintw(12, 61, "  ");
    mvprintw(13, 61, "  ");
    mvprintw(14, 61, "  ");
    mvprintw(15, 17, "                                              ");
    for (int i = 0; i < 40; i++) {
        mvprintw(11, 18, "%-40ls", repeatStr(L"▒", i));
        refresh();
        usleep(100000);
    }
    move(0,0);
    clear();
    setFooterText(" F1=Help     F2 = Skip     F3= Replace step     ENTER= Continue                   ");
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0, 0);
    printw("                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0,0);
    printw("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "     Thank you for typing out your license key.                                   \n"
           "     The computer must perform a multitude of steps to verify                     \n"
           "     the license key is valid.                                                    \n"
           "                                                                                  \n"
           "     While the floppy disk and license key may be legit, an                       \n"
           "     connection to our local activation servers must be completed                 \n"
           "     to ensure this license key has not been used before.                         \n"
           "                                                                                  \n"
           "     Please look below.                                                           \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "     - FLOPPY DISK ACTIVATION                                                     \n"
           "                                                                                  \n"
           "     ->");                                           
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(COLOR_PAIR(FLOPPY_ACTIVATION));
    printw("VERIFY WITH INTERNET CONNECTION");
    attroff(COLOR_PAIR(FLOPPY_ACTIVATION));
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    printw( "                                            \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "     Please press ");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND_ENTER));
    attron(A_BOLD);
    printw("ENTER");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND_ENTER));
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    printw(" to continue with the activation                           \n"
           "                                                                                  \n");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(A_STANDOUT);
    refresh();

    while (1) {
        int c = getch();
        if (c == '\n' || c == KEY_ENTER) break;
        else if (c == KEY_F(2)) goto skip;
    }
    clear();
    attroff(A_STANDOUT);
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0, 0);
    printw("                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0,0);
    addwstr(L"Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "     Please wait while we verify your license key.                                \n"
           "                                                                                  \n"
           "     This proces may take up to one minute.                                       \n"
           "     The progress could be seen below.                                            \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "   ┌─────────────────────────────────────────────────────────────────────────┐    \n"
           "   │                                                                         │    \n"
           "   └─────────────────────────────────────────────────────────────────────────┘    \n");
    playSoundInNewThread("Dial_up_modem_noises.ogg");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    for (int i = 0; i < 71; i++) {
        attron(COLOR_PAIR(LICENSEKEY_BACKGROUND_ENTER));
        mvprintw(14, 5, "%-71ls", repeatStr(L"▒", i));
        attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND_ENTER));
        setFooterText(" Establishing connection with network modem.                                     ");
        if (i > 10) setFooterText(" Dialing activation servers...                                                   ");
        if (i > 25) setFooterText(" Sending information... (968KB)                                                  ");
        if (i > 50) setFooterText(" Recieving information....                                                       ");
        if (i > 60) setFooterText(" Finishing...                                                                    ");
        refresh();
        usleep(300000);
    }
    stopSound();
skip:
    clear();
    attroff(A_STANDOUT);
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0, 0);
    printw("                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0,0);
    addwstr(L"Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "     Thank you for attempting to activate MS-DOS!                                 \n"
           "                                                                                  \n"
           "     Your computer will restart within a few seconds...                           \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "   ┌─────────────────────────────────────────────────────────────────────────┐    \n"
           "   │                                                                         │    \n"
           "   └─────────────────────────────────────────────────────────────────────────┘    \n");  
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(A_STANDOUT);
    refresh();
    pthread_t restart_now_thread;
    pthread_create(&restart_now_thread, NULL, waitForEnter, NULL);
    setFooterText(" ENTER = RESTART NOW                                                              ");
    attroff(A_STANDOUT);
    attron(COLOR_PAIR(FLOPPY_ACTIVATION));
    for (int i = 71; i > 0; i--) {
        if (!can_restart) break;
        mvprintw(9, 5, "%-71ls", repeatStr(L"▒", i));
        refresh();
        usleep(100000);
    }
    if (can_restart) restart();
}

void license_key() {
    clear();
    init_pair(LICENSEKEY_BACKGROUND, COLOR_WHITE, COLOR_BLUE);
    init_pair(LICENSEKEY_BACKGROUND_ENTER, COLOR_YELLOW, COLOR_BLUE);
    setFooterText(" ENTER=Continue     ESCAPE=Check     F1=Help     F2=Remove Colour     F3=Restart ");
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    move(0, 0);
    printw("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n" //44-45
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"            
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
    move(0, 0);
    printw("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n");

    printw("     Welcome to Activation.                                                       \n");
    sleep(1);
    refresh();
    printw("                                                                                  \n");
    printw("     The activation program activates, or checks MS-DOS 6.22 to                   \n");
    sleep(1);
    refresh();
    printw("     run on your computer.                                                        \n");
    sleep(1);
    refresh();
    printw("                                                                                  \n");
    printw("          -   To set up LICENSE KEY ACTIVATION, press ");            
    attron(A_BOLD);
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND_ENTER));
    printw("ENTER");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND_ENTER));
    attron(COLOR_PAIR(LICENSEKEY_BACKGROUND)); 
    printw(".                      \n");
    sleep(1);
    refresh();
    printw("          -   To set up LICENSE KEY CHECK, press ESCAPE.                          \n");
    sleep(1);
    refresh();
    printw("                                                                                  \n");
    printw("     Note: This program requires an internet connection and faliure               \n");
    sleep(1);
    refresh();
    printw("     will lock down your PC.                                                      \n");
    sleep(1);
    refresh();
    printw("                                                                                  \n");
    printw("     If you want a more detailed guide, press F1.                                 \n");
    sleep(1);
    refresh();
    printw("                                                                                  \n");
    printw("                                                                                  \n");
    printw("                                                                                  \n");
    attroff(COLOR_PAIR(LICENSEKEY_BACKGROUND));
    attron(A_STANDOUT);
    attroff(A_STANDOUT);
    refresh();
    while (process_licensekey_input) {
        int c = getch();
        switch(c) {
            case '\n':
            case KEY_ENTER:
                license_activation();
            break;
            case 033:

            break;
            case KEY_F(1):

            break;
            case KEY_F(2):
                clear();
                move(0, 0);
                prints("Microsoft MS-DOS 6.22 Activation                                                  \n"
           " ==============================                                                   \n"
           "                                                                                  \n"
           "     Welcome to Activation.                                                       \n"
           "                                                                                  \n"
           "     The activation program activates, or checks MS-DOS 6.22 to                   \n"
           "     run on your computer.                                                        \n"
           "                                                                                  \n"
           "          -   To set up LICENSE KEY ACTIVATION, press ");  
           prints("ENTER");
           prints(".                      \n");
           prints(
           "          -   To set up LICENSE KEY CHECK, press ESCAPE.                          \n"
           "                                                                                  \n"
           "     Note: This program requires an internet connection and faliure               \n"
           "     will lock down your PC.                                                      \n"
           "                                                                                  \n"
           "     If you want a more detailed guide, press F1.                                 \n"
           "                                                                                  \n"
           "                                                                                  \n"
           "                                                                                  \n");
           mvprintw(20, 0, " ENTER=Continue     ESCAPE=Check     F1=Help     F2=Remove Colour     F3=Restart ");
            break;
            case KEY_F(3):
                clear();
                move(0, 0);
                    prints("Welcome to MS-DOS 6.22.\n"
           "(C) Microsoft\n\n"
           "Your computer has been locked down for possible piracy.\n"
           "Please select an option below.\n\n"
           "LICENSE KEY ACTIVATION                                 \n"
           "EMPLOYEE ACTIVATION                                    \n"
           "ACTIVATE MS-DOS USING A MODEM                          \n"
           "SHUT DOWN COMPUTER                                     \n\n");
           prints("You may need an internet connection to verify that everything is correct.\n");
           move(OPTION_OFFSET, 0);
                process_main_input = TRUE;
                return;
            break;
        }
    }
}

void shut_down() {
    exit(0);
}

void modem() {

}

void onExit() {
    endwin();
    system("stty sane; clear;");
}

int main() {
    atexit(onExit);
    system(cmd_clear);
#ifdef _WIN32
    printf("Welcome to MS-DOS 6.22.\n"
           "(C) Microsoft\n\n"
           "Your computer shows no sign of piracy.");
    exit(0);
#endif
    int current_option = 0, old_option = 0;
    const char *options[4] = {
        "LICENSE KEY ACTIVATION                                 \n",
        "EMPLOYEE ACTIVATION                                    \n",
        "ACTIVATE MS-DOS USING A MODEM                          \n",
        "SHUT DOWN COMPUTER                                     \n"
    };
    printf("\a");
    setlocale(LC_ALL, "C.utf8");
    initscr();
    clear();
    refresh();
    curs_set(0);
    prints("Welcome to MS-DOS 6.22.\n"
           "(C) Microsoft\n\n");
    printw("Your computer has been locked down for possible piracy.\n");
    refresh();
    sleep(1);
    printw("Please select an option below.\n\n");
    refresh();
    sleep(1);
    printw("LICENSE KEY ACTIVATION                                 \n");
    refresh();
    usleep(100000);
    printw("EMPLOYEE ACTIVATION                                    \n");
    refresh();
    usleep(100000);
    printw("ACTIVATE MS-DOS USING A MODEM                          \n");
    refresh();
    usleep(100000);
    printw("SHUT DOWN COMPUTER                                     \n\n");
    refresh();
    keypad(stdscr, true);
    raw();
    noecho();
    if (!has_colors()) {
        printw("Warning: no colors");
        refresh();
        while (1) {}
    }
    start_color();
    printw("You may need an internet connection to verify that everything is correct.\n");
    refresh();
    move(OPTION_OFFSET, 0);
    while (process_main_input) {
        int c = getch();
        switch (c) {
            case KEY_DOWN:
                current_option++;
                if (current_option > 3) current_option = 3;
                attron(A_STANDOUT);
                move(current_option+OPTION_OFFSET, 0);
                printw(options[current_option]);
                attroff(A_STANDOUT);
                mvprintw(current_option-1+OPTION_OFFSET, 0, options[current_option-1]);
            break;
            case KEY_UP:
                current_option--;
                if (current_option < 0) current_option = 0;
                attron(A_STANDOUT);
                move(current_option+OPTION_OFFSET, 0);
                printw(options[current_option]);
                attroff(A_STANDOUT);
                mvprintw(current_option+1+OPTION_OFFSET, 0, options[current_option+1]);
            break;
            case '\n':
            case KEY_ENTER:
                process_main_input = FALSE;
                if (current_option == 0) license_key();
                else if (current_option == 1) employee();
                else if (current_option == 2) modem();
                else if (current_option == 3) shut_down();
            break;
            case 'q': 
                exit(0);
            break;
        } 
        old_option = current_option;
        refresh();
    }
    endwin();
    return 0;
}