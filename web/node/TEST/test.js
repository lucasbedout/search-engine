var io = require('./node_modules/socket.io/lib/socket.io.js');
var socket = io.connect('http://localhost');
  socket.on('news', function (data) {
    console.log(data);
    socket.emit('my other event', { my: 'data' });
	});
