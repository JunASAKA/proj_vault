#pragma once

#include "vault.hpp"
#include <sqlite3.h>

namespace db_manager
{
	void test();
	std::string get_json_data_from_db(std::string nickname);

}