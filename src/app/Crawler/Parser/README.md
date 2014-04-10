#Installation des librairies.
##Tidy :

- Pré-requis :
  - cloner le répo git correspondant : 


##Pour compiler le fichier test_parse_lib.cpp
`sudo g++ test.cpp -o test -I/usr/local/include  -L/usr/local/lib -libtidy \`pkg-config --cflags --libs libxml++-2.6`
