TryToSurvive:main.o fichiers.o format.o crash.o
	gcc main.o fichiers.o format.o crash.o -o TryToSurvive

main.o:./Src/main.c
	gcc -c ./Src/main.c

fichiers.o:./Lib/Fichiers/fichiers.c
	gcc -c ./Lib/Fichiers/fichiers.c

format.o:./Lib/Format/format.c
	gcc -c ./Lib/Format/format.c

crash.o:./Lib/Crash/crash.c
	gcc -c ./Lib/Crash/crash.c

clean:
	rm *.o TryToSurvive
