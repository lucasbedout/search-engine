/**
 * File Name: index.js,
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This is start up file which is defines custom globals related to path and more.
 */
global.basePath = __dirname;
global.viewsPath = basePath+'/application/views';

var apps = require('./application/apps');
apps.start();