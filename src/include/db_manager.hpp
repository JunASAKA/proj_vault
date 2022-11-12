#pragma once

#include <iostream>
#include "user_record.hpp"
#include <sqlite3.h>

namespace db_manager
{

	bool storage_into_db(user_record *input_user_record);
	user_record *get_user_record_from_db(std::string codename);
	bool update_record(user_record *input_user_record);
	bool delete_record(std::string codename);
	void list_all_keys();
	bool if_extist_key(std::string codename);
}