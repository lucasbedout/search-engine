#include "DatabaseManager.h"

int main(int argc, char const *argv[])
{
	DatabaseManager manager("tcp://192.168.1.27:3306", "root", "bitnami", "searchengine");
	return 0;
}