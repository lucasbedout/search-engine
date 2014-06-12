/**
 * AuthController
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

var passport = require('passport');

module.exports = { 
    
    // Renvoie à l'accueil si pas de paramètres
    login: function(req, res) {
        res.redirect('/');
    },

    // Traite le formulaire envoyé par l'utilisateur, si le login échoue on renvoie à l'accueil
    process: function(req,res){
        passport.authenticate('local', function(err, user, info){
            if ((err) || (!user)) {
              res.redirect('/');
              return;
            }
            req.logIn(user, function(err){
              if (err) res.redirect('/');
              console.log(user.username + ' is connected');
              res.redirect('/');
            });
        })(req, res);
    },

    // Déconnexion de l'utilisateur
    logout: function (req, res) {
    	req.logout();
        res.view('home/index', {
            'user': req.user,
            'error': ''
        });
    }  
};

module.exports.blueprints = {
	actions: true,
	rest: true,
	shortcuts: true
};
