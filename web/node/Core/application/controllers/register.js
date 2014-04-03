/**
 * File Name: register.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: To render registration form.
 */
var dbcontrol = require('../models/dbcontrol');
var jqtpl = require('jqtpl');
var fs = require("fs");

var getRegistrationTemplate = function(getRegistrationPageArgs) {
  var session = getRegistrationPageArgs.session;
  jqtpl.template('registration', fs.readFileSync(viewsPath
      + '/registration.html', 'utf-8'));
  return jqtpl.tmpl('registration', {
    title : "Registration",
    currentUser : session.username
  });
};


var getRegistrationPage = function(request,response,next){
  request.session.regenerate(function(err) {
    // will have a new session here
  });
  request.session.username = 'Guest';
  var setRegistrationPageArgs = {};
  setRegistrationPageArgs.session = request.session;
  response.send(getRegistrationTemplate(setRegistrationPageArgs));
};

var registrationFormSubmit = function(request,response,next){
  var username = request.body.username;
  var password = request.body.password;
  //var userModel = dbcontrol.userCollection;
  var user = new dbcontrol.userCollection();
  user.name = username;
  user.password = password;
  user.save(function(err) {
    if (err) {
      console.log(err);
      request.session.username = 'Guest';

    } else {
      request.session.username = username;
      response.redirect('/');
    }
  });
};

exports.registrationHandler = function(request,response,next){
  if(request.method == 'GET')
    getRegistrationPage(request,response,next);
  else if(request.method == 'POST')
    registrationFormSubmit(request,response,next); 
};