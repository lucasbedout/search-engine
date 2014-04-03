/**
 * File Name: router.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This is simply enables menus which are defined in menus.js file.
 */
var menus = require('./menus.js').menus;
module.exports = function(app){
  //Error Handler
  app.error(function(error, request, response, next) {
    console.log('App Error : ' + error);
    response.end('Please try again later');
  });
  
  menus.forEach(function(menu,key){
    if(menu){
    var file = menu.file;
    var fn = menu.callback;
      menu.methods.split(',').forEach(function(method){
        app[method](menu.url,function(request,response,next){
          require(file)[fn](request,response,next);
        });
      });
    }
  });
};



