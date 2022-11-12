#include "user_record.hpp"

user_record::user_record(std::string input_codename, std::string input_username, std::string input_password, std::string input_urls)
{
	codename = input_codename;
	username = input_username;
	password = input_password;
	urls = input_urls;
}