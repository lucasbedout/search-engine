Configuration des machines virtuelles 
=====================================

Accès aux machines
------------------

Toutes les machines ont un serveur SSH installé dessus. 

Elles sont configurées pour être utilisées localement ou sur une Freebox V5, sur VmWare VM > Settings > Network adapter > Host-only pour une configuration locale. En théorie pas d'accès à internet dans ce cas-là.

- **Master : HAProxy - DNS - SQL Management - Crawler**
    - 192.168.1.24
    - 4 Go de RAM, 2 coeurs de processeur
    - hostname : master, FQDN : master.project.lan (pingable depuis le hostname sur le réseau privé bien sur)
    - Serveur DNS principal
    - Serveur HAProxy (répartition de charge pour les serveurs web)
    
- **Slave 1 : MySQL - Node.js**
    - 192.168.1.25
    - hostname : slave1, FQDN : slave1.project.lan

- **Slave 1 : MySQL - Node.js**
    - 192.168.1.26
    - hostname : slave2, FQDN : slave2.project.lan
    
- **Slave 1 : MySQL - Node.js**
    - 192.168.1.27
    - hostname : slave3, FQDN : slave3.project.lan
    - 
Toutes les machines ont la même configuration user/passwords, c'est simple, tout est *bitnami* : 

- root password : *bitnami*
- username : *bitnami*
- user password : *bitnami*

