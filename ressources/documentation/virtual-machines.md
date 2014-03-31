Configuration des machines virtuelles 
=====================================

Accès aux machines
------------------

Toutes les machines ont un serveur SSH installé dessus. 

Elles sont configurées pour être utilisées localement ou sur une Freebox V5, sur VmWare VM > Settings > Network adapter > Host-only pour une configuration locale. En théorie pas d'accès à internet dans ce cas-là.

- **Master : HAProxy - DNS - Crawler**
    - 192.168.1.24
    - 4 Go de RAM, 2 coeurs de processeur
    - hostname : master, FQDN : master.project.lan (pingable depuis le hostname sur le réseau privé bien sur)
    - Serveur DNS principal
    - Serveur HAProxy (répartition de charge pour les serveurs web)
    
- **Slave 1 : MySQL - Node.js**
    - 192.168.1.25
    - 1 Go de RAM
    - hostname : slave1, FQDN : slave1.project.lan
    - Serveur MySQL - clusterisé via Galera

- **Slave 1 : MySQL - Node.js**
    - 192.168.1.26
    - 1 Go de RAM
    - hostname : slave2, FQDN : slave2.project.lan
    - Serveur MySQL - clusterisé via Galera

    
- **Slave 1 : MySQL - Node.js**
    - 192.168.1.27
    - 1 Go de RAM
    - hostname : slave3, FQDN : slave3.project.lan
    - Serveur MySQL - clusterisé via Galera



Toutes les machines ont la même configuration user/passwords, c'est simple, tout est *bitnami* : 

- root password : *bitnami*
- username : *bitnami*
- user password : *bitnami*

Tester et utiliser la config
------------------

**Cluster Node.js**

Le cluster est configuré de façon à répartir la charge en round robin sur les 3 nodes. 
Afin de ne pas perdre les sockets d'un client, un cookie est mis en place sur son navigateur afin qu'il interroge toujours le même serveur.
Un certificat SSL a été mis en place afin de crypter les connexions.

Sur *master*, démarrer le service haproxy 

<code>sudo service haproxy start</code>

Créer un fichier hello.js identique sur les 3 serveurs web, y placer ce code 
<pre>
 var http = require('http');
var url = require('url');
var spawn = require ('child_process').spawn;
 
var listenport = 1337;
 
// Chomp function (delete the \n)
String.prototype.chomp = function () {
return this.replace(/(\n|\r)+$/, '');
};
 
// HTTP request
function onRequest(req, res) {
console.log("New request: "+req.url);
res.writeHead(200, {'Content-Type': 'text/plain'});
res.write('Hello World');
res.end();
};
 
// Create the HTTP server
http.createServer(onRequest).listen(listenport);
 
// Get the hostname (FQDN)
var listenaddress = spawn('hostname', ['-f']);
listenaddress.stdout.on('data', function (data) {
var fqdn = new String(data);
console.log('Server running listenning http://'+fqdn.chomp()+':'+listenport+'/');
});
</pre>

Lancer ensuite le serveur
<code>node hello.js</code>

Puis envoyez une requête HTTP vers le port 80 de master (http://192.168.1.24 depuis votre navigateur windows), vous devriez voir "Hello world" s'afficher en HTTPS.
Testez avec différents navigateurs, vous devriez voir des messages type <code> /request </code> sur les terminaux des serveurs web.

**Cluster MySQL**

Le cluster MySQL est composé des 3 serveurs slave1, slave2 et mysql.
Démarrez MySQL sur le serveur mysql (mysql.project.lan) avec la commande suivante <code>service mysql start --wsrep-new-cluster</code>
Démarrez mysql sur les 2 autres serveurs (slave1 slave2) avec la commande <code>sudo service mysql start </code>

Entre la commande suivante pour vérifier que tout le monde est bien opérationnel 

<code> mysql -u root -e 'SELECT VARIABLE_VALUE as "cluster size" FROM INFORMATION_SCHEMA.GLOBAL_STATUS WHERE VARIABLE_NAME="wsrep_cluster_size"'</code>

La sortie devrait être celle-ci 

<pre>
+--------------+
| cluster size |
+--------------+
| 3            |
+--------------+
</pre>
