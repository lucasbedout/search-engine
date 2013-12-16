# Résumé de l'algorithme

Le crawler doit être capable de parcourir les pages web à travers les protocoles HTTP et FTP. Une fois la première URL donnée, il doit passer seul de liens en liens afin de crawler le maximum de pages.
Etant un crawler pour intranet, il devra vérifier que le nom de domaine/IP est bien celui contenu dans l'URL de départ et/ou l'URL précédente.

# Eléments de solution en langage courant

Crawler
-------

- Le crawler sera un objet instancié en fonction du nombre de liens à crawler, de la charge du serveur et de la demande "utilisateur"
- Chaque instance du crawler lira les pages "non lues" dans l'ordre de leur position en base de données
- Chaque inscription d'un nouveau lien en base de données donnera lieu à une demande d'instance traitée par le serveur
- Un crawler meurt lorsqu'il n'y a plus de lien en attente en base de données


Suvi des liens
--------------

- Solution 1 : Lecture du document, chaque lien parsé est ajouté à la base de données 