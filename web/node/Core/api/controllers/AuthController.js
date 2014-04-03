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

var passwport = require('passport');

module.exports = { 
    
    // Affiche le formulaire de login
    login: function(req, res) {
    	res.view();
    },

    // Traite le formulaire envoyé par l'utilisateur
    process: function(req, res) {
    	passport.authenticate('local', function(err, user, info) {
    		if ((err) || (!user)) {
    			return res.send({
    				message: 'login failed'
    			});
    			res.send(err);
    		}
    		req.logIn(user, function(err) {
    			if (err) res.send(err);
    			return res.send({
    				message: 'login successful'
    			});
    		});
    	})(req, res);
    },

    // Déconnexion de l'utilisateur
    logout: function (req, res) {
    	req.logout();
    	res.send('logout successful');
    }  
};

module.exports.blueprints = {
	actions: true,
	rest: true,
	shortcuts: true
};
