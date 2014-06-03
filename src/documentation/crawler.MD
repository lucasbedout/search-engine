#Documentation Crawler

##Qu'est-ce qu'il fait ?
-------------------

Il crawl ! Il navigue dans le web via un principe très simple :
  - Il part d'une page dont l'URL est fournie, pour ensuite la scanner et la stocker
  - Il passe ensuite aux autres pages dont il a trouvé les liens dans la page initiale et ce de manière infinie.

Résumé : Il navigue donc à travers une liste de page web.

##Comment il fonctionne ?
--------------------

Il est exécuté depuis une commande ./Crawler avec un argument `URLDELAPAGE`. Ceci nous donne : `./Crawler URLDELAPAGE`.
  - Il part de l'url principale et ensuite il la download et appelle le parser.
  - Il extrait tous les liens de la page parsée et il les ajoute à la pile de liens qu'il doit crawler (un unique lien ne peut s'y trouver qu'une seule fois)
  - Il passe au lien suivant et il fera de même pour tous les liens.
