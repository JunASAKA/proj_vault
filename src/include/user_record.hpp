#pragma once

#include <iostream>
#include <string>

class user_record
{
public:
	std::string codename;
	std::string username;
	std::string password;
	std::string urls;

	user_record(std::string input_codename, std::string input_username = "", std::string input_password = "", std::string input_urls = "");
};