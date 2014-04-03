/**
 * isAuthenticated
 *
 * @module      :: Policy
 * @description :: Simple policy to allow any authenticated user
 *                 Assumes that your login action in one of your controllers sets `req.session.authenticated = true;`
 * @docs        :: http://sailsjs.org/#!documentation/policies
 *
 */
module.exports = function (req, res, ok) {
 
  // User accepté, on passe à la suite, sinon on redirige vers le login
  var is_auth = req.isAuthenticated()
  if (is_auth) 
  	return next();
  else 
  	return res.redirect("/login");
};
