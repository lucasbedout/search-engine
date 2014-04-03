/**
 * File Name: apps.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This file is used to hook application and start up file.
 */
var start = function() {
  var control = require('./controllers/supercontrol');
  control.bootup();
};

// Exports
exports.start = start;