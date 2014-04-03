/**
 * File Name: login.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: To render login page.
 */
var dbcontrol = require('../models/dbcontrol');
var jqtpl = require('jqtpl');
var fs = require("fs");

var getLoginTemplate = function(getLoginPageArgs) { 
  var session = getLoginPageArgs.session;
  jqtpl.template('loginpage', fs.readFileSync(viewsPath + '/login.html',
      'utf-8'));
  return jqtpl.tmpl('loginpage', {
    title : "Login",
    currentUser : session.username
  });
};

var getLoginPage = function(request,response,next){
  if (request.session.username == 'Guest') {
    var setLoginPageArgs = {};
    setLoginPageArgs.session = request.session;
    response.send(getLoginTemplate(setLoginPageArgs));
  } else {
    response.redirect('/');
  }
};

var loginFormSubmit = function(request,response,next){
  var username = request.body.username;
  var password = request.body.password;
  var user = dbcontrol.userCollection;
  
  user.isRegisteredUser(username, password, function(authenticated) {
    if (authenticated) {
      request.session.username = username;
      response.redirect('/');
    } else {
      response.redirect('/register');
    }
  });
};

exports.loginHandler = function(request,response,next){
  if(request.method == 'GET')
    getLoginPage(request,response,next);
  else if(request.method == 'POST')
    loginFormSubmit(request,response,next);    
};