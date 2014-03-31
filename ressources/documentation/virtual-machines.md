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

** Cluster Node.js **

Sur *master*, démarrer le service haproxy 

<code>sudo service haproxy start</code>

Créer un fichier hello.js identique sur les 3 serveurs web, y placer ce code 
<code>
//
// A JavaScript based on Node.js
//
// Nicolas Hennion (aka) Nicolargo
//
// GPL v3.0
//
 
var http = require('http');
var url = require('url');
var spawn = require ('child_process').spawn;
 
//**********
// Variables
//**********
 
var listenport = 1337;
 
//**********
// Functions
//**********
 
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
 
//*************
// Main program
//*************
 
// Create the HTTP server
http.createServer(onRequest).listen(listenport);
 
// Get the hostname (FQDN)
var listenaddress = spawn('hostname', ['-f']);
listenaddress.stdout.on('data', function (data) {
var fqdn = new String(data);
console.log('Server running listenning http://'+fqdn.chomp()+':'+listenport+'/');
});
</code

Lancer ensuite le serveur
<code>node hello.js</code>

Puis envoyez une requête HTTP vers le port 80 de master (http://192.168.1.24 depuis votre navigateur windows), vous devriez voir "Hello world" s'afficher en HTTPS.

