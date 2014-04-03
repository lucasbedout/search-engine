/**
 * File Name: home.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: To render home page.
 */
var dbcontrol = require('../models/dbcontrol');
var jqtpl = require('jqtpl');
var fs = require("fs");

var getHomePage = function(getHomePageArgs) {
  var session = getHomePageArgs.session;
  jqtpl.template('homepage', fs.readFileSync(viewsPath + '/page.html',
      'utf-8'));
  return jqtpl.tmpl('homepage', {
    title : "Home",
    currentUser : session.username
  });
};

exports.homePageHandler = function(request,response,next){
  var setHomePageArgs = {};
  if (typeof request.session.username != 'string'
      || request.session.username == '') {
    request.session.username = 'Guest';
  }
  setHomePageArgs.session = request.session;
  response.send(getHomePage(setHomePageArgs));
};