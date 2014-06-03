CXXFLAGS= -Wall `pkg-config --cflags --libs libxml++-2.6`
LDFLAGS= -L /usr/local/lib -ltidy -lmysqlcppconn

# création de l'exécutable 
all: file.o keywords.o misc.o page.o parse.o ranking.o
		g++ -o test file.o keywords.o misc.o page.o parse.o ranking.o $(LDFLAGS) $(CXXFLAGS) 
 
file.o: ../Crawler/File/file.cpp ../Crawler/File/file.h
		g++ -c ../Crawler/File/file.cpp -o file.o
 
keywords.o: ../Crawler/Keywords/keywords.cpp ../Crawler/Keywords/keywords.h
		g++ -c ../Crawler/Keywords/keywords.cpp -o keywords.o
 
misc.o: ../Crawler/Misc/misc.cpp ../Crawler/Misc/misc.h
		g++ -c ../Crawler/Misc/misc.cpp -o misc.o

page.o: ../Crawler/Page/page.cpp ../Crawler/Page/page.h
		g++ -c ../Crawler/Page/page.cpp -o page.o $(LDFLAGS) $(CXXFLAGS)

parse.o: ../Crawler/Parser/parse.cpp ../Crawler/Parser/parse.h
		g++ -c ../Crawler/Parser/parse.cpp -o parse.o $(LDFLAGS) $(CXXFLAGS)

ranking.o: ranking.cpp ranking.h
		g++ -c ranking.cpp
# suppression des fichiers temporaires
clean:
		rm -rf *.o
 
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
		rm -rf test