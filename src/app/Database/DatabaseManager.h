/* Database Manager
 |
 | Cette classe s'occupe de gérer la connexion, l'enregistrement et la récupération de données en base
 | Elle gère les objets de type "Page"
 |
 |
  */


#include <iostream>

#include "mysql_connection.h"
#include "../Class/Page.h"
#include "../Class/misc.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
 #include <cppconn/prepared_statement.h>

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

	std::vector<Page> getPages(std::string keywords)
	{
		std::vector<std::string> search = splitString(keywords, ' ');
		std::vector<Page> pages;
		std::vector<int> pages_id;

		int keywords_size = search.size();

		sql::PreparedStatement *stmt;
		sql::ResultSet *res;

		for(int i = 0 ; i < keywords_size ; i++) 
		{
			try {
 				stmt = _conn->prepareStatement("SELECT * FROM pages WHERE content LIKE ?");
				stmt->setString(1, "%" + search[i] + "%");
				res = stmt->executeQuery();
				while(res->next())
				{
					if(std::find(pages_id.begin(), pages_id.end(), res->getInt(1)) == pages_id.end())
					{	
						std::vector<std::string> page_keywords = splitString(res->getString("keywords"), ' ');
						Page page(res->getInt(1), page_keywords, res->getString("content"), res->getString("title"), res->getString("url"), res->getString("description"));
						pages.push_back(page);
						pages_id.push_back(res->getInt(1));
					} 
				}
			} catch (sql::SQLException &e) {
				std::cout << "# ERR: SQL Exception in " << __FILE__;
				std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
				std::cout << "# ERR: " << e.what();
				std::cout << " (MySQL error code : " << e.getErrorCode();
				std::cout << ", SQLState : " << e.getSQLState() << " ) " << std::endl;
			}			
		}

		return pages;
	}

	bool savePage(Page page)
	{
		// on vérifie les infos de la page et on les sauvegarde 
	}


};