CXXFLAGS= -Wall `pkg-config --cflags --libs libxml++-2.6`
LDFLAGS= -L/usr/local/lib -ltidy -lcurl

# création de l'exécutable 
all: file.o keywords.o misc.o page.o parse.o crawler.o main.o
		g++ -o test file.o keywords.o misc.o page.o parse.o crawler.o main.o $(LDFLAGS) $(CXXFLAGS) 
 
file.o: Parser/File/file.cpp Parser/File/file.h
		g++ -c Parser/File/file.cpp -o file.o
 
keywords.o: Parser/Keywords/keywords.cpp Parser/Keywords/keywords.h
		g++ -c Parser/Keywords/keywords.cpp -o keywords.o
 
misc.o: Parser/Misc/misc.cpp Parser/Misc/misc.h
		g++ -c Parser/Misc/misc.cpp -o misc.o

page.o: Parser/Page/page.cpp Parser/Page/page.h
		g++ -c Parser/Page/page.cpp -o page.o $(LDFLAGS) $(CXXFLAGS)

parse.o: Parser/Parse/parse.cpp Parser/Parse/parse.h
		g++ -c Parser/Parse/parse.cpp -o parse.o $(LDFLAGS) $(CXXFLAGS)

crawler.o: crawler.cpp crawler.h
		g++ -c crawler.cpp -o crawler.o $(LDFLAGS) $(CXXFLAGS)

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