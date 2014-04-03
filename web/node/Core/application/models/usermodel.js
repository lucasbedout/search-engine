/**
 * File Name: usermodel.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This is used to manage user collection in mongodb with mongoose friendly.
 */
var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var crypto = require('crypto');
var userSchema = new Schema({
  name : String,
  password : String
});

userSchema.path('password').set(function(pwd) {
  return crypto.createHash('md5').update(pwd).digest('hex');
});

userSchema.statics.isRegisteredUser = function(username, password, callback) {
  var md5_pwd = crypto.createHash('md5').update(password).digest('hex');
  return this.find({
    $and : [ {
      name : username
    }, {
      password : md5_pwd
    } ]
  }, function(err, docs) {
    if (docs.length == 1) {
      callback(true);
    } else {
      callback(false);
    }
  });
};

// Exports
exports.userCollection = mongoose.model('user', userSchema);


