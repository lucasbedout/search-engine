CXXFLAGS= -Wall `pkg-config --cflags --libs libxml++-2.6`
LDFLAGS= -L/usr/local/lib -ltidy

# création de l'exécutable 
all: file.o keywords.o misc.o page.o parse.o main.o
		g++ -o test file.o keywords.o misc.o page.o parse.o main.o $(LDFLAGS) $(CXXFLAGS) 
 
file.o: File/file.cpp File/file.h
		g++ -c File/file.cpp -o file.o
 
keywords.o: Keywords/keywords.cpp Keywords/keywords.h
		g++ -c Keywords/keywords.cpp -o keywords.o
 
misc.o: Misc/misc.cpp Misc/misc.h
		g++ -c Misc/misc.cpp -o misc.o

page.o: Page/page.cpp Page/page.h
		g++ -c Page/page.cpp -o page.o $(LDFLAGS) $(CXXFLAGS)

parse.o: Parse/parse.cpp Parse/parse.h
		g++ -c Parse/parse.cpp -o parse.o $(LDFLAGS) $(CXXFLAGS)

main.o: main.cpp
		g++ -c main.cpp -o main.o $(LDFLAGS) $(CXXFLAGS)

# suppression des fichiers temporaires
clean:
		rm -rf *.o
		rm -rf */*.h.gch
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
		rm -rf test