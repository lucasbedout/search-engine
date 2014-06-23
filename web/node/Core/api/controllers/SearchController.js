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
    var level = req.param('level');
    if (typeof level === 'undefined')
    {
        level = 2;
    }

    console.log(level + ' : ' + words);
    var completeData = '';
    var pages = new Array();
    var start = Date.now();

    // Avant tout on teste si une recherche n'a pas été faite avec ces mots clés
    Search.find()
        .where({ keywords: words})
        .sort('id desc')
        .exec(function(err, search) {
            if (search.length)
            {
                completeData = search[0].result;
                var search_result = JSON.parse(completeData);
                console.log(search);
                var pages = new Array();

                for (var i in search_result.search.results) {
                    pages.push(search_result.search.results[i]);
                }
                var end = Date.now();
                var elapsed = (end - start) / 1000;
                res.view('search/results', {
                    'length': 25,
                    'search_id': search[0].id,
                    'keywords': words,
                    'pages': pages,
                    'elapsed': elapsed,
                    'user': req.user
                });
            } else {
                client = net.connect({
                    port: 3001,
                    host: '192.168.1.24'
                }, function() {
                    client.write(level + ';' + words);
                    console.log(level + ';' + words)
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
                        }

                        var end = Date.now();
                        var elapsed = (end - start) / 1000;

                        Search.create({
                            keywords: words,
                            result: completeData,
                            time: elapsed
                        }).done(function(err, search) {
                            if (err) {
                                res.view('home/index', {
                                    error: 'Impossible to connect the database',
                                    user: req.user
                                });
                            } else {
                                res.view('search/results', {
                                    'length': 25,
                                    'search_id': search.id,
                                    'keywords': words,
                                    'pages': pages,
                                    'elapsed': elapsed,
                                    'user': req.user
                                });
                            }
                        })
                    }
                })
            }
        });
  },

  luck: function(req, res) {
      var words = req.param('search-words');
      var level = 2;
      var completeData = '';
      var pages = new Array();

      client = net.connect({
          port: 3001,
          host: '192.168.1.24'
      }, function() {
          client.write(level + ';' + words);
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
  },

  more: function(req, res) {
      var search = Search.findOne(req.param('id'), function(err, search) {
          var from = parseInt(req.param('from'));
          var results = JSON.parse(search.result);
          var next = new Array();
          var length = from + 25;

          if (from == 0) {
              for (var i in results.search.results) {
                  next.push(results.search.results[i]);
              }

              res.view('search/results', {
                  'length': 25,
                  'search_id': search.id,
                  'keywords': search.keywords,
                  'pages': next,
                  'elapsed': search.time,
                  'user': req.user
              });

          } else {
              var index = from - 25;
              var future_length = from + 25;
              console.log(future_length);
              var count = 0;

              for (var i = index ; i < (from + 1) ; i++) {
                  if (typeof results.search.secundaries[i] != 'undefined')
                  {
                      var page = Page.findOne(results.search.secundaries[i]).done(function(err, page) {
                          next.push(page);
                          count++;
                          if (count == 25)
                          {
                              console.log('On envoie la view');
                              res.view('search/results', {
                                  'length': future_length,
                                  'search_id': search.id,
                                  'keywords': search.keywords,
                                  'pages': next,
                                  'elapsed': search.time,
                                  'user': req.user
                              });
                          }
                      });
                  }
              }
          }
      });
  }
};
