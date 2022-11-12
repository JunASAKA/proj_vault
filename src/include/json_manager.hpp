#pragma once

#include <iostream>
#include "user_record.hpp"
#include <string>
#include <json/json.h>

namespace json_manager
{
	std::string format_json(std::string input_json);
}