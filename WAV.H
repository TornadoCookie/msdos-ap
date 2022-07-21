#ifndef ogg_h
#define ogg_h

int playSound(char *fname, int seconds);
void playSoundInNewThread(char *fname, int seconds);
void stopSound();

#endif