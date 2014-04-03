/**
 * File Name: supercontrol.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This file hold server configuration and hooks to link controllers.
 */
var express = require('express');
var app = express.createServer();
var MongoStore = require('connect-mongo')(express); // Session control
//Enable Object Cache for CSS and Js files
require('./dynamiccache');

app.configure(function configuration() {
	app.use(express.cookieParser());
	app.use(express.session({
		secret : "basic server",
		cookie : {
			maxAge : (120 * 60 * 1000) //2 hrs
		},
		store : new MongoStore({
			host : 'localhost',
			port : 27017,
			db : 'basicserverdb',
			collection : 'session',
			stringify : false,
			clear_interval : 5
		})
	}));
	app.use(express.bodyParser());
	app.use(cacheCSS());
	app.use(cacheJS());
});

//Include Menus and respective handlers
require('./routers')(app);

// Exports
exports.bootup = function(){
  
  var appStart = function(){
    app.listen('9001', function starting(err) {
      console.log('Server has been started in 9001');
    });
  };
  
  //Create Database Connection
  require('mongoose').connect('mongodb://localhost:27017/basicserverdb', function(
      err, dbins) {
    if (err){
      console.log('DB ' + err); 
      process.exit();
    }   
    else{
      console.log('Database has been connected');
      if(typeof appStart === 'function')
        appStart();
    }
  }); ;
};
