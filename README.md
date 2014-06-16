# SEARCH ENGINE - 2PJT SUPINFO

## Instructions de déploiement 

*Ces instructions sont données pour le déploiement sur une seule machine. Le programme peut-être clusterisé, à votre choix pour l'implémentation des différents serveurs. Nous traiterons uniquement un serveur Linux*

### Configuration du serveur

Tout d'abord, installer g++, gcc et les outils de développement si ce n'est pas déjà fait
<code>sudo apt-get install build-essential</code>

--------------

Installer ensuite Node.js

<code> sudo apt-get install python-software-properties nodejs </code>

Puis ajouter le module Sails grâce à npm

<code> npm install -g sails </code>

--------------

Installer MySQL 

<code> sudo apt-get install mysql-server </code>

--------------
Ajouter ensuite les librairies utiles au C++ 

Tidy : 

  - Cloner le répo git correspondant : https://github.com/w3c/tidy-html5
  - Puis suivre les indications : 
    - "For Linux/BSD/OSX platforms, you can build and install the tidy command-line tool from the source code using the         following steps."
      
      1. `sudo make -C build/gmake/`
      2. `sudo make install -C build/gmake/`

--------------

libxml++ :

  - libxml2
    - `sudo apt-get install libxml2`
  - libxml++
    - `sudo apt-get install libxml++2.6-dev libxml++2.6-doc` le doc uniquement si vous en avez besoin.

--------------

Boost :

<code>sudo apt-get install libboost-all-dev</code>

MySQL Connector : 

<code>sudo apt-get install libmysqlcppconn-dev</code>

### Configuration et lancement des applications

** Web App **

En fonction de la configuration IP de votre serveur, vous devez éditer l'application node.js pour qu'elle puisse communiquer avec votre backend. 

Pour celà il suffit de se rendre dans `web/node/Core/api/Controllers/SearchController.js` et de modifier `192.168.1.24` par localhost ou l'IP de votre choix (qui doit être celle où écoute le C++). 

De même dans `web/node/Core/api/Controllers/CrawlController.js`, remplacer l'IP par localhost.

Dernière modification, dans `web/node/Core/config/adapters.js`, remplacer 192.168.1.27 par localhost ou l'IP de votre choix (de même pour l'username/password de votre base de données).

Sur la machine, se rendre dans le dossier `web/node/Core/` et entrer la commande `npm install` afin d'installer tous les modules node.js utilisés par Sails.

Lancer MySQL `sudo service mysql.server start`

Vous pouvez à présent lancer l'application avec la commande `sails lift`. Elle est alors accessible sur le port 1337 de la machine en HTTP.

** C++ **

Compilation des exécutables

Rendez vous dans le dossier `src/app/Crawler` et exécutez la commande `make`. 

Faites de même dans `src/app/Research`.

Reculez ensuite d'un dossier dans `src/app/` et exécutez la commande `node server.js`. La console devrait lancer le serveur et attendre des informations.

Vous pouvez alors entrer une recherche ou une demande de crawl dans l'application web !


