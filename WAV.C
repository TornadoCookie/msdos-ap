#include <stdlib.h>
#include "WAV.H"
#include <stdbool.h>
#include "CROSSPLATFORM.H"
#include <string.h>

//having a seperate 

#ifdef _WIN32

void stopSound() {
    system("DOS/AP/WAV_PLAYBACK.COM stop");
}

int playSound(char *fname, int seconds) {
    return system(strcat("DOS/AP/WAV_PLAYBACK.COM play", fname));
}

void playSoundInNewThread(char *fname, int seconds) {
    system(strcat("start /b DOS/AP/WAV_PLAYBACK.COM play ", fname));
}

#elif defined(__linux__)

#include <stdio.h>

void stopSound() {
    system("DOS/AP/WAV_PLAYBACK.COM stop");
}

int playSound(char *fname, int seconds) {
	char second_str[100];
	sprintf(second_str, "%d", seconds);
	system(strcat(strcat(strcat("DOS/AP/WAV_PLAYBACK.COM play 48000 ", second_str), " < "), fname));
}

void playSoundInNewThread(char *fname, int seconds) {
    puts("Playing sound in new thread...");
    char main_str[1000] = "DOS/AP/WAV_PLAYBACK.COM play 48000 2 ";
	char second_str[1000];
	sprintf(second_str, "%d", seconds);
    puts("base");
    char *base = strcat(main_str, second_str);
    puts("base_plus_thing");
    char *base_plus_thing = strcat(base, " < \'");
    puts("base_fname");
    char *base_fname = strcat(base_plus_thing, fname);
    puts("cmd");
    char * cmd = strcat(base_fname, "\' &");
    printf("cmd is %s\n", cmd);
	system(cmd);
}
#endif