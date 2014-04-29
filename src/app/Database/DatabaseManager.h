/* Database Manager
 |
 | Cette classe s'occupe de gérer la connexion, l'enregistrement et la récupération de données en base
 | Elle gère les objets de type "Page"
 |
 |
  */


#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class DatabaseManager 
{
private:
	std::string _host;
	std::string _user;
	std::string _pass;
	std::string _database;

	sql::Connection *_conn;

public:
	DatabaseManager(std::string host, std::string user, std::string pass, std::string database)
	{
		sql::Driver *driver;

		// On place les attributs et on ouvre la connexion
		if (!host.empty() && !user.empty() && !database.empty())
		{
			_host = host;
			_user = user;
			_pass = pass;
			_database = database;

			try {
				driver = get_driver_instance();
				_conn = driver->connect(_host, _user, _pass);
				_conn->setSchema(_database);
				std::cout << "Connection ok on " << _host << std::endl;
			} catch (sql::SQLException &e) {
				std::cout << "# ERR: SQL Exception in " << __FILE__;
				std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
				std::cout << "# ERR: " << e.what();
				std::cout << " (MySQL error code : " << e.getErrorCode();
				std::cout << ", SQLState : " << e.getSQLState() << " ) " << std::endl;
			}
			
		}
	}
};