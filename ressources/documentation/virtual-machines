Configuration des machines virtuelles 
=====================================

Accès aux machines
------------------

Toutes les machines ont un serveur SSH installé dessus. 

Elles sont configurées pour être utilisées localement ou sur une Freebox V5, sur VmWare VM > Settings > Network adapter > Host-only pour une configuration locale. En théorie pas d'accès à internet dans ce cas-là.

- **Master 1 : Management Node 1 + SQL Node 1**
    - 192.168.1.24
    - hostname : master1, FQDN : master1.project.lan (pingable depuis le hostname sur le réseau privé bien sur)
    - Serveur DNS principal
    
- **Master 2 : Management Node 2 + SQL Node 2**
    - 192.168.1.25
    - hostname : master2, FQDN : master2.project.lan

- **Data 1 : Data Node 1**
    - 192.168.1.26
    - hostname : data1, FQDN : data1.project.lan
    
- **Data 2 : Data Node 3**
    - 192.168.1.26
    - hostname : data1, FQDN : data1.project.lan
        
Toutes les machines ont la même configuration user/passwords, c'est simple, tout est *bitnami* : 

- root password : *bitnami*
- username : *bitnami*
- user password : *bitnami*

