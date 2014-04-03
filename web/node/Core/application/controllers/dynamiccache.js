/**
 * File Name: dynamiccache.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This file is defined to store static content in 
 * javascript object in-order to reduce file IO and improve the site performance.
 */
var fs = require("fs");

module.exports = cacheCSS = function() {
  var css = {};
  return function(request, response, next) {
    if (request.headers['accept'].indexOf('text/css') != -1) {
      response.setHeader('Content-Type', 'text/css');
      if (typeof css[request.url] != 'string') {
        fs.readFile(basePath + '/application/views/' + request.url,
            'utf-8', function(err, data) {
              if (err)
                console.log(err);
              else {
                css[request.url] = data;
                response.send(css[request.url]);
              }
            });
      } else {
        response.send(css[request.url]);
      }
    } else {
      next();
    }
  };
};

module.exports = cacheJS = function() {
  var JS = {};
  return function(request, response, next) {
    if (request.url.indexOf('.js') != -1) {
      response.setHeader('Content-Type', 'text/javascript');
      if (typeof JS[request.url] != 'string') {
        fs.readFile(basePath + '/application/views/' + request.url,
            'utf-8', function(err, data) {
              if (err)
                console.log(err);
              else {
                JS[request.url] = data;
                response.send(JS[request.url]);
              }
            });
      } else {
        response.send(JS[request.url]);
      }
    } else {
      next();
    }
  };
};



