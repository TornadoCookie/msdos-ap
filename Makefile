
DOS/AP/ACTIVATION.COM : ACTIVATION.o
	gcc $^ -o $@ -lncurses

DOS/AP/AP.COM : AP.o OGG.o
	gcc $^ -o $@ -lncurses -lvorbisfile -lasound

DOS/AP/APSCREEN.exe : APSCREEN.o OGG.o
	gcc $^ -o $@ -lncurses -lvorbisfile -lasound

DOS/AP/APDAEMON.COM : APDAEMON.o DOS/AP/ACTIVATION.COM DOS/AP/APSCREEN.exe DOS/AP/AP.COM
	gcc APDAEMON.o -o $@ -lncurses

%.o : %.C
	gcc -c $^

clean: 
	rm *.o

all: DOS/AP/APDAEMON.COM