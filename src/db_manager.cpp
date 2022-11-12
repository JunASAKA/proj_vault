#include "db_manager.hpp"

namespace db_manager
{

	std::string get_json_data_from_db(std::string nickname)
	{

		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		std::string return_json_data = "";

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "successful" << std::endl;
		}
		else
		{
			std::cout << "error" << std::endl;
		}

		std::string sqlSentence = "select json from rec where nickname = \"" + nickname + "\";";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "pass." << std::endl;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				return_json_data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
				// std::cout << json_data << std::endl;
			}
		}
		else
		{
			std::cout << "error: sy";
		}
		sqlite3_finalize(stmt);

		if (sql)
		{
			sqlite3_close_v2(sql);
			sql = nullptr;
		}

		return return_json_data;
	}










	void test()
	{
		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "successful" << std::endl;
		}
		else
		{
			std::cout << "error" << std::endl;
		}

		// const char *sqlSentence = "select json from rec where nickname = \"test2\";";
		std::string sqlSentence = "select json from rec where nickname = \"test2\";";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "pass." << std::endl;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				std::string json_data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
				std::cout << json_data << std::endl;
			}
		}
		else
		{
			std::cout << "error: sy";
		}
		sqlite3_finalize(stmt);

		if (sql)
		{
			sqlite3_close_v2(sql);
			sql = nullptr;
		}
	}
}