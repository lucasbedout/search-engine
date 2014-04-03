/**
 * File Name: menus.js, 
 * Author: hilarudeens,
 * Date Created: 10th Oct 2012,
 * Description: This is used defined various menu's url and their respective
 * callbacks. This is collection object. Each Object should have following things,
 * url -> menu path which will be give in browser's address bar.
 * callback -> This is function having express module friedly aruguments. This is initiate page build.
 * menthods -> This field define what are the methods given into the path.
 * file -> This field defines which file has "callback" function.
 * 
 * To add more menus
 * -----------------
 * For example, there is url "/books" which shows list of books in shop.
 * Just do it following,
 * append following object as last element of array.
 * {
   "url" : "/books",
   "callback" : "showBooks",
   "methods" : "get",
   "file" : "./book.js"
   }
 * where book.js is a file, you should be created within "controllers" folder or directory and define 
 * which html fine used to generate response. 
 * 
 */

exports.menus = [
{
  "url" : "/",
  "callback" : "homePageHandler",
  "methods" : "get",
  "file" : "./home.js"
}, 
{
  "url" : "/login",
  "callback" : "loginHandler",
  "methods" : "get,post",
  "file" : "./login.js"
}, 
{
  "url" : "/register",
  "callback" : "registrationHandler",
  "methods" : "get,post",
  "file" : "./register.js"
}/*,
{
   "url" : "/books",
   "callback" : "showBooks",
   "methods" : "get",
   "file" : "./books.js"
}*/
];