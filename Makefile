
DOS/AP/ACTIVATION.COM : ACTIVATION.o
	gcc $^ -o $@ -lncursesw

DOS/AP/AP.COM : AP.o OGG.o
	gcc $^ -o $@ -lncursesw -lvorbisfile -lasound

DOS/AP/APSCREEN.exe : APSCREEN.o OGG.o
	gcc $^ -o $@ -lncursesw -lvorbisfile -lasound

DOS/AP/APDAEMON.COM : APDAEMON.o DOS/AP/ACTIVATION.COM DOS/AP/APSCREEN.exe DOS/AP/AP.COM
	gcc APDAEMON.o -o $@ -lncursesw

%.o : %.C
	gcc -c $^

clean: 
	rm *.o

all: DOS/AP/APDAEMON.COM