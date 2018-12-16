TryToSurvive:main.o fichiers.o format.o crash.o
	gcc main.o fichiers.o format.o crash.o -o TryToSurvive -Wall

main.o:./Src/main.c
	gcc -c ./Src/main.c -Wall

fichiers.o:./Lib/Fichiers/fichiers.c
	gcc -c ./Lib/Fichiers/fichiers.c -Wall

format.o:./Lib/Format/format.c
	gcc -c ./Lib/Format/format.c -Wall

crash.o:./Lib/Crash/crash.c
	gcc -c ./Lib/Crash/crash.c -Wall

clean:
	rm *.o TryToSurvive
