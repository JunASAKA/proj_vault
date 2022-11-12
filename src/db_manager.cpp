#include "db_manager.hpp"

namespace db_manager
{

	user_record *get_user_record_from_db(std::string codename)
	{

		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		user_record *return_user_record = new user_record(codename);

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] db opened successfully." << std::endl;
		}
		else
		{
			std::cout << "[debug (db_manager)] error(s) occured when opening db in function \"get_user_record_from_db\"." << std::endl;
		}

		std::string sqlSentence = "select username, password, urls from record where codename = \"" + codename + "\";";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] sql sentence seems good." << std::endl;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				return_user_record->username = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
				return_user_record->password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
				return_user_record->urls = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			}
		}
		else
		{
			std::cout << "[debug (db_manager)] sql setence went wrong in function \"get_user_record_from_db\".";
		}
		sqlite3_finalize(stmt);

		if (sql)
		{
			sqlite3_close_v2(sql);
			sql = nullptr;
		}

		return return_user_record;
	}

	bool storage_into_db(user_record *input_user_record)
	{

		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] db opened successfully." << std::endl;
		}
		else
		{
			std::cout << "[debug (db_manager)] error(s) occured when opening db in function \"storage_into_db\"" << std::endl;
		}

		std::string sqlSentence = "INSERT INTO record (codename, username, password, urls) VALUES(\"" + input_user_record->codename + "\", \"" + input_user_record->username + "\", \"" + input_user_record->password + "\", \"" + input_user_record->urls + "\");";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] sql operations done." << std::endl;
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			return true;
		}
		else
		{
			std::cout << "[debug (db_manager)] sql operations failed in function \"storage_into_db\"." << std::endl;
			sqlite3_finalize(stmt);
			return false;
		}
	}

	bool update_record(user_record *input_user_record)
	{
		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] db opened successfully." << std::endl;
		}
		else
		{
			std::cout << "[debug (db_manager)] error(s) occured when opening db in function \"update_record\"" << std::endl;
		}

		std::string sqlSentence = "update record set username=\"" + input_user_record->username + "\", password=\"" + input_user_record->password + "\", urls=\"" + input_user_record->urls + "\" where codename=\"" + input_user_record->codename + "\";";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] sql operations done." << std::endl;
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			return true;
		}
		else
		{
			std::cout << "[debug (db_manager)] sql operations failed in function \"update_record\"." << std::endl;
			sqlite3_finalize(stmt);
			return false;
		}
	}

	bool delete_record(std::string codename)
	{
		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] db opened successfully." << std::endl;
		}
		else
		{
			std::cout << "[debug (db_manager)] error(s) occured when opening db in function \"delete_record\"" << std::endl;
		}

		std::string sqlSentence = "delete from record where codename=\"" + codename + "\";";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] sql operations done." << std::endl;
			sqlite3_step(stmt);
			sqlite3_finalize(stmt);
			return true;
		}
		else
		{
			std::cout << "[debug (db_manager)] sql operations failed in function \"delete_record\"." << std::endl;
			sqlite3_finalize(stmt);
			return false;
		}
	}

	void list_all_keys()
	{
		sqlite3 *sql = NULL;
		const char *path = "../test.db";

		int32_t result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] db opened successfully." << std::endl;
		}
		else
		{
			std::cout << "[debug (db_manager)] error(s) occured when opening db in function \"list_all_keys\"" << std::endl;
		}

		std::string sqlSentence = "select codename from record;";
		sqlite3_stmt *stmt = NULL;

		result = sqlite3_prepare_v2(sql, sqlSentence.c_str(), -1, &stmt, NULL);

		if (result == SQLITE_OK)
		{
			std::cout << "[debug (db_manager)] sql sentence seems good." << std::endl;
			while (sqlite3_step(stmt) == SQLITE_ROW)
			{
				std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)) << std::endl;
			}
		}
		else
		{
			std::cout << "[debug (db_manager)] sql setence went wrong in function \"list_all_keys\".";
		}
		sqlite3_finalize(stmt);

		if (sql)
		{
			sqlite3_close_v2(sql);
			sql = nullptr;
		}

		return;
	}

}