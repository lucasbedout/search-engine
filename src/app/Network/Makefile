CXXFLAGS= -Wall `pkg-config --cflags --libs libxml++-2.6`
LDFLAGS= -L /usr/local/lib -ltidy
LBFLAGS= -I /usr/include/boost -lboost_system -lmysqlcppconn

# création de l'exécutable 
all: file.o keywords.o misc.o page.o parse.o network.o 
		g++ -o test file.o keywords.o misc.o page.o parse.o network.o $(LBFLAGS) $(LDFLAGS) $(CXXFLAGS) -g
 
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