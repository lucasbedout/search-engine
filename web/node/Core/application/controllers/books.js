/**
 * File Name: books.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: Added for show example.
 */
var jqtpl = require('jqtpl');
var fs = require("fs");
var getBooksPage = function(getshowBooksPageArgs) { 
  jqtpl.template('bookspage', fs.readFileSync(viewsPath + '/books.html',
      'utf-8'));
  return jqtpl.tmpl('bookspage', {
    title : "Books",
  });
};
exports.showBooks = function(request,response,next){
  var setshowBooksPageArgs = {};
  response.send(getBooksPage(setshowBooksPageArgs));
};