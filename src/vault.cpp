#include "clipp.hpp"
#include "vault.hpp"
#include <cstdlib>

int main(int argc, char *argv[])
{
	enum class mode
	{
		storage,
		read,
		generate,
		update,
		_delete_,
		help
	};
	mode selected = mode::help;

	std::string codename = "";
	std::string username = "";
	std::string password_unencrypted = "";
	std::string json_unencrypted = "";
	std::string urls = "";

	bool output_as_json = false;

	auto storage_mode = (clipp::command("storage").set(selected, mode::storage),
						 clipp::option("--codename") & clipp::value("codename", codename) % "codename",
						 clipp::option("--username") & clipp::value("username", username) % "username",
						 clipp::option("--password") & clipp::value("password_unencrypted", password_unencrypted) % "password",
						 clipp::option("--urls") & clipp::value("urls", urls) % "urls",
						 clipp::option("--json") & clipp::value("json_unencrypted", json_unencrypted) % "json");

	auto read_mode = (clipp::command("read").set(selected, mode::read),
					  clipp::option("--codename") & clipp::value("codename", codename) % "codename",
					  clipp::option("--json-fmt").set(output_as_json, true).doc("output as json"));

	auto generage_mode = (clipp::command("storage").set(selected, mode::generate));

	auto update_mode = (clipp::command("update").set(selected, mode::update),
						clipp::option("--codename") & clipp::value("codename", codename) % "codename",
						clipp::option("--username") & clipp::value("username", username) % "username",
						clipp::option("--password") & clipp::value("password_unencrypted", password_unencrypted) % "password",
						clipp::option("--urls") & clipp::value("urls", urls) % "urls",
						clipp::option("--json") & clipp::value("json_unencrypted", json_unencrypted) % "json");

	auto delete_mode = (clipp::command("delete").set(selected, mode::_delete_),
						clipp::option("--codename") & clipp::value("codename", codename) % "codename");

	auto cli = ((storage_mode | read_mode | generage_mode | update_mode | delete_mode | clipp::command("help").set(selected, mode::help)),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 0.00a" << std::endl; })
					.doc("show version"),
				clipp::option("-h", "--help").set(selected, mode::help).doc("show this help message"));

	if (parse(argc, argv, cli))
	{
		switch (selected)
		{
		case mode::storage:
			if (codename.empty())
			{
				std::cout << "Error: codename is neccessary." << std::endl;
				break;
			}
			else
			{
				user_record *input_record = new user_record(codename, username, password_unencrypted, urls);
				std::cout << db_manager::storage_into_db(input_record) << std::endl;
				delete input_record;
			}
			break;
		case mode::read:
			if (codename.empty())
			{
				std::cout << "Error: codename is neccessary." << std::endl;
				break;
			}
			else
			{
				user_record *output_record = db_manager::get_user_record_from_db(codename);
				std::cout << "codename: " << output_record->codename << std::endl
						  << "username: " << output_record->username << std::endl
						  << "password: " << output_record->password << std::endl
						  << "urls: " << output_record->urls << std::endl
						  << std::endl;
				delete output_record;
			}
			break;
		case mode::generate:
			// TODO: generate;
			break;

		case mode::update:
			if (codename.empty())
			{
				std::cout << "Error: codename is neccessary." << std::endl;
				break;
			}
			else
			{
				user_record *input_record = db_manager::get_user_record_from_db(codename);
				if(!username.empty()){
					input_record->username = username;
				}
				if(!password_unencrypted.empty()){
					input_record->password = password_unencrypted;
				}
				if(!urls.empty()){
					input_record->urls = urls;
				}
				std::cout << db_manager::update_record(input_record) << std::endl;
				delete input_record;
			}
			break;

		case mode::_delete_:
			if (codename.empty())
			{
				std::cout << "Error: codename is neccessary." << std::endl;
				break;
			}
			else
			{
			}
			break;
		case mode::help:
			std::cout << clipp::make_man_page(cli, "zhixueUtilities") << std::endl;
			break;
		default:
			break;
		}
	}
	else
	{
		std::cout << clipp::make_man_page(cli, "vault") << std::endl;
	}

	return 0;
}
