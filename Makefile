
DOS/AP/ACTIVATION.COM : ACTIVATION.o
	gcc $^ -o $@ -lncursesw

DOS/AP/AP.COM : AP.o WAV.o
	gcc $^ -o $@ -lncursesw

DOS/AP/APSCREEN.exe : APSCREEN.o WAV.o
	gcc $^ -o $@ -lncursesw

DOS/AP/WAV_PLAYBACK.COM : WAV_PLAYBACK.o
	gcc $^ -o $@ -lasound

DOS/AP/APDAEMON.COM : APDAEMON.o DOS/AP/ACTIVATION.COM DOS/AP/APSCREEN.exe DOS/AP/AP.COM DOS/AP/WAV_PLAYBACK.COM
	gcc APDAEMON.o -o $@ -lncursesw

%.o : %.C
	gcc -c $^

clean: 
	rm *.o

all: DOS/AP/APDAEMON.COM