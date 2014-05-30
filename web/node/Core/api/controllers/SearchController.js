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
    var numberOfResults;
    var completeData = '';
    var n = 0;
    var pages = new Array();

  	client = net.connect({
          		port: 13,
          		host: '192.168.1.24'
          	}, function() {
                client.write('2');
            		client.write(words);
            	});

    client.setEncoding('utf8');

	client.on('data', function(data) {
        if (n == 0) {
            numberOfResults = parseInt(data);
            console.log(numberOfResults + ' résultats trouvés');
            n++;
        }
        else {
            completeData += data;
        }
      });

    client.on('end', function() {

            var parts = completeData.split('|$');
            parts.pop();
            var length = parts.length;
            for (var i = 0; i < length; i++) {
                console.log(parts[i]);
                pages.push(JSON.parse(parts[i]));
            };
            res.view('search/results', {
                'pages': pages,
                'user': req.user });
    })
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
