TryToSurvive:main.o fichiers.o format.o
	gcc main.o fichiers.o format.o -o TryToSurvive

main.o:./Src/main.c
	gcc -c ./Src/main.c

fichiers.o:./Lib/fichiers.c
	gcc -c ./Lib/fichiers.c

format.o:./Lib/format.c
	gcc -c ./Lib/format.c

clean:
	rm *.o TryToSurvive
