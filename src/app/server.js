var net = require('net');
var exec = require('child_process').exec;

net.createServer(onRequest_search).listen(3001);
net.createServer(onRequest_crawl).listen(3002);

function onRequest_search (socket) {
    var keywords, search, searchOutput;

    socket.on('data', function(data) {
        keywords = data.toString();
        search = exec('./Research/test 2 ' + keywords, function(err, stdout, stderr) {
            console.log(stdout);
            socket.end(stdout);
        });
    });
}

function onRequest_crawl (socket) {
    var url;

    socket.on('data', function(data) {
        url = data.toString();
        console.log(url);
        crawl = exec('./Crawler/crawler ' + url);
    });

    socket.end();
}


