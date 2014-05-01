## Installation des libs sur Ubuntu

### Boost

<code>sudo apt-get install libboost-all-dev</code>

### Mysql-connector 

<code>sudo apt-get install libmysqlcppconn-dev</code>

Les librairies sont installées dans /usr/include, pour compiler il suffit d'ajouter -lboost ou -lmysqlcppconn par exemple

## How To Use

Pour l'utiliser, vous devez avoir l'architecture de dossiers suivante : 

- Class/
	- misc.h
	- misc.cpp
- DatabaseManager.h
- main.cpp (votre code)


Pour compiler voici la commande : 

<code>g++ -o test -I /usr/include/ * ../Class/misc.cpp -lmysqlcppconn</code>

### Utilisation 

Pour se connecter à la base de données
<code>DatabaseManager manager("tcp://192.168.1.27:3306", "username", "pass", "database");</code>

Pour sauvegarder une page, le manager gère seul s'il doit créer une nouvelle page ou en updater une
La fonction return un booléen, true si la sauvegarde a réussi.
<code>manager.savePage(page);</code>

Pour récupérer les pages en fonctions des mots clés entrés par l'utilisateur
La fonction retourne un vector<Page>
<code>manager.getPages("coucou hello keyword3");</code>
