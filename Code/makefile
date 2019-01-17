TryToSurvive:main.o fichiers.o crash.o stat.o ui.o
	gcc -L/usr/local/lib main.o fichiers.o crash.o stat.o ui.o -o TryToSurvive -Wall -lgsl -lgslcblas -lm

main.o:./Src/main.c
	gcc -c ./Src/main.c

fichiers.o:./Lib/Fichiers/fichiers.c
	gcc -c ./Lib/Fichiers/fichiers.c

crash.o:./Lib/Crash/crash.c
	gcc -c ./Lib/Crash/crash.c

stat.o: ./Lib/Stat/stat.c
	gcc -c ./Lib/Stat/stat.c

ui.o: ./Lib/UI/ui.c
	gcc -c ./Lib/UI/ui.c

clean:
	rm *.o TryToSurvive
