CXXFLAGS= -Wall `pkg-config --cflags --libs libxml++-2.6`
LDFLAGS= -L /usr/local/lib -ltidy
LBFLAGS= -I /usr/include/boost -lboost_system

# création de l'exécutable 
all: file.o keywords.o misc.o page.o parse.o network.o 
		g++ -o test file.o keywords.o misc.o page.o parse.o network.o $(LBFLAGS) $(LDFLAGS) $(CXXFLAGS) 
 
file.o: ../Crawler/Parser/File/file.cpp ../Crawler/Parser/File/file.h
		g++ -c ../Crawler/Parser/File/file.cpp -o file.o
 
keywords.o: ../Crawler/Parser/Keywords/keywords.cpp ../Crawler/Parser/Keywords/keywords.h
		g++ -c ../Crawler/Parser/Keywords/keywords.cpp -o keywords.o
 
misc.o: ../Crawler/Parser/Misc/misc.cpp ../Crawler/Parser/Misc/misc.h
		g++ -c ../Crawler/Parser/Misc/misc.cpp -o misc.o

page.o: ../Crawler/Parser/Page/page.cpp ../Crawler/Parser/Page/page.h
		g++ -c ../Crawler/Parser/Page/page.cpp -o page.o $(LDFLAGS) $(CXXFLAGS)

parse.o: ../Crawler/Parser/Parse/parse.cpp ../Crawler/Parser/Parse/parse.h
		g++ -c ../Crawler/Parser/Parse/parse.cpp -o parse.o $(LDFLAGS) $(CXXFLAGS)

network.o: serverAsyn.cpp serverAsyn.h 
		g++ -c serverAsyn.cpp -o network.o $(LBFLAGS);

# suppression des fichiers temporaires
clean:
		rm -rf *.o
		rm -rf ../Crawler/Parser/*/*.h.gch
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
		rm -rf test