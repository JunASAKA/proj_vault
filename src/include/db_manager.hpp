#pragma once

#include <iostream>
#include "user_record.hpp"
#include <sqlite3.h>

namespace db_manager
{

	bool storage_into_db(user_record *input_user_record);
	user_record *get_user_record_from_db(std::string codename);
	bool update_record(user_record *input_user_record);
}