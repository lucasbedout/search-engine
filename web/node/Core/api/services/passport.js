var passport = require('passport'),
	LocalStrategy = require('passport-local').Strategy,
	bcrypt = require('bcrypt');

// Code des helpers pour l'authentification
// On récupère un user par son ID, gestion du cas où il n'est pas trouvé
function findById(id, fn) {
	User.findOne(id).done(function (err, user) {
		if (err) {
			return fn(null, null);
		} else {
			return fn(null, user);
		}
	});
}

// On récupère un user par son Username, gestion du cas où il n'est pas trouvé
function findByUsername(username, fn) {
	User.findOne({
		username: username
	}).done(function (err, user) {
		if (err) {
			return fn(null, null);
		} else {
			return fn(null, user);
		}
	});
}

/* Configuration de la session passport
/  Pour supporter les sessions persistentes, passport doit pouvoir sérialiser
/  et désérialiser les users dans et hors de la session. Il suffit de charger l'ID
/  en session pour sérialiser et de trouver l'utilisateur par ID à la désérialisation
*/

passport.serializeUser(function(user, done) {
	done(null, user.id);
});

passport.deserializeUser(function(id, done) {
	findById(id, function(err, user) {
		done(err, user);
	});
});

/* Utilisation de LocalStrategy
/  Les stratégie ont besoin de la fonction verify, qui prend en argument les identifiants
/  et invoke un callback avec un objet utilisateur
*/

passport.use(new LocalStrategy(
	function(username, password, done) {
		// Vérification asynchrone
		process.nextTick(function() {
			findByUsername(username, function(err, user) {
				if (err) 
					return done(null, err)
				if (!user) {
					return done(null, false, {
						message: 'Unknown user' + username
					});
				}
				bcrypt.compare(password, user.password, function(err, res) {
					if (!res)
						return done(null, false, {
							message: 'Invalid password'
						});
					var returnUser = {
						username: user.username,
						createdAt: user.createdAt,
						id: user.id,
						email: user.email
					};
					return done(null, returnUser, {
						message: 'Logged in successfully'
					});
				});
			})
		});
	}
));