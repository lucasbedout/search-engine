#Installation des librairies.
##Tidy :

--------------
- Pré-requis :
  - Cloner le répo git correspondant : https://github.com/w3c/tidy-html5
  - Puis suivre les indications : 
    - "For Linux/BSD/OSX platforms, you can build and install the tidy command-line tool from the source code using the         following steps."
      
      1. `sudo make -C build/gmake/`
      2. `sudo make install -C build/gmake/`

---------------
- Vérifier que tout est bien installé :
  - Où sont les fichiers ?
    - Un fichier de librairie devrait être ici :
    `bitnami@ubuntu:/usr/local/lib$ ls` il devrait y avoir `libtidy.a`
    - Les .h devraient être là :
    `bitnami@ubuntu:/usr/local/include$`il devrait y avoir `tidy`.


##libxml++ :

Là c'est un peu plus ennuyeux ! (nan c'est une blague)

--------------

- Pré-requis :
  - libxml2
    - `sudo apt-get install libxml2`
  - libxml++
    - `sudo apt-get install libxml++2.6-dev libxml++2.6-doc` le doc uniquement si vous en avez besoin.

--------------
- Vérifier que tout est bien installé :
  - On devrait avoir dans `/usr/local/include` 
    1. `libxml++`
    2. `libxml2`


##Pour compiler le fichier test_parse_lib.cpp
sudo g++ test_parse_lib.cpp -o test -I/usr/local/include  -L/usr/local/lib -ltidy \`pkg-config --cflags --libs libxml++-2.6\`

