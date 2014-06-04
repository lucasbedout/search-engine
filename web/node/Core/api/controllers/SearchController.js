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


var net = require('net');

module.exports = {
    
  search: function(req, res) {
  	var words = req.param('search-words');
    var numberOfResults;
    var completeData = '';
    var pages = new Array();
    var start = Date.now();

  	client = net.connect({
          		port: 3001,
          		host: '192.168.1.24'
          	}, function() {
            		client.write(words);
            	});

    client.setEncoding('utf8');

	client.on('data', function(data) {
        completeData += data.toString().replace(/(\r\n|\n|\r)/gm," ");
    });

    client.on('end', function() {
        var search = JSON.parse(completeData);
        var pages = new Array();
        if (!search.search.success)
        {
            res.view('home/index', {
                error: 'No result found',
                user: req.user
            });
        } else {

            for (var i in search.search.results) {
                pages.push(search.search.results[i]);
                console.log(pages[i]);
            }

            var end = Date.now();
            var elapsed = (end - start) / 1000;

            res.view('search/results', {
                'keywords': words,
                'pages': pages,
                'elapsed': elapsed,
                'user': req.user
            });
        }
    })
  },

  luck: function(req, res) {
      var words = req.param('search-words');
      var completeData = '';
      var pages = new Array();

      client = net.connect({
          port: 3001,
          host: '192.168.1.24'
      }, function() {
          client.write(words);
      });

      client.setEncoding('utf8');

      client.on('data', function(data) {
          completeData += data.toString().replace(/(\r\n|\n|\r)/gm," ");
      });

      client.on('end', function() {
          var search = JSON.parse(completeData);
          var pages = new Array();
          if (!search.search.success)
          {
              res.redirect('/');
          }

          for (var i in search.search.results) {
              pages.push(search.search.results[i]);
              console.log(pages[i]);
          }

          var page = pages[0];
          console.log(page.url);
          res.redirect(page.url);
      })
  }
};
