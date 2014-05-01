/**
 * SearchController
 *
 * @module      :: Controller
 * @description	:: A set of functions called `actions`.
 *
 *                 Actions contain code telling Sails how to respond to a certain type of request.
 *                 (i.e. do stuff, then send some JSON, show an HTML page, or redirect to another URL)
 *
 *                 You can configure the blueprint URLs which trigger these actions (`config/controllers.js`)
 *                 and/or override them with custom routes (`config/routes.js`)
 *
 *                 NOTE: The code you write here supports both HTTP and Socket.io automatically.
 *
 * @docs        :: http://sailsjs.org/#!documentation/controllers
 */

// On va utiliser la lib net 

var net = require('net');

module.exports = {
    
  search: function(req, res) {
  	var words = req.param('search-words');
  		client = net.connect({
  			port: 13,
  			host: '192.168.1.24'
  		}, function() {
        client.write('2');
  			client.write(words);
  		});

  		client.on('data', function(data) {
  			console.log(data.toString());
  		})

  	console.log('Recherche : ' + words);
  	res.redirect('/');
  },

  luck: function(req, res) {
  	var words = req.param('search-words');
  		client = net.connect({
  			port: 13,
  			host: '192.168.1.24'
  		}, function() {
        client.write('2');
  			client.write(words);
  		});

  		client.on('data', function(data) {
  			console.log(data.toString());
  		})
  	console.log('Alors, on veut de la chance ?');
  	res.redirect('/');
  }

};
