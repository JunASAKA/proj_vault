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
		help
	};
	mode selected = mode::help;

	// std::string tchToken;
	// std::string stuToken;
	//  std::string hwId;
	//  std::string stuId;
	//  std::string stuHwId;
	//  std::string listIndex;
	//  std::string stuUsername;
	//  std::string stuPasswd;
	//  std::string tchUsername;
	//  std::string tchPasswd;
	//  std::string attachmentUrl;
	//  std::string clazzId;

	// //std::string finaloutStr;

	// bool useIndex = false;
	// bool completed = false;
	// bool isClkHw = false;
	// //bool useClazzId = false;
	// bool redoWithStuId = false;

	std::string nickname = "";
	std::string username = "";
	std::string password_unencrypted = "";
	std::string json_unencrypted = "";

	bool output_as_json = false;

	// auto getListMode = (clipp::command("getList").set(selected, mode::getList),
	// 					clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
	// 					clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto storage_mode = (clipp::command("storage").set(selected, mode::storage),
						 clipp::option("--nickname") & clipp::value("nickname", nickname) % "nickname",
						 clipp::option("--username") & clipp::value("username", username) % "username",
						 clipp::option("--password") & clipp::value("password_unencrypted", password_unencrypted) % "password",
						 clipp::option("--json") & clipp::value("json_unencrypted", json_unencrypted) % "json");

	auto read_mode = (clipp::command("read").set(selected, mode::read),
					  clipp::option("--nickname") & clipp::value("nickname", nickname) % "nickname",
					  clipp::option("--json-fmt").set(output_as_json, true).doc("output as json"));

	auto generage_mode = (clipp::command("storage").set(selected, mode::generate));

	auto cli = ((storage_mode | read_mode | generage_mode | clipp::command("help").set(selected, mode::help)),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 0.00a" << std::endl; })
					.doc("show version"),
				clipp::option("-h", "--help").set(selected, mode::help).doc("show this help message"));

	if (parse(argc, argv, cli))
	{
		// if (std::getenv("stuUsername") != nullptr)
		// {
		// 	stuUsername = std::getenv("stuUsername");
		// }
		// if (std::getenv("stuPasswd") != nullptr)
		// {
		// 	stuPasswd = std::getenv("stuPasswd");
		// }
		// if (std::getenv("tchUsername") != nullptr)
		// {
		// 	tchUsername = std::getenv("tchUsername");
		// }
		// if (std::getenv("tchPasswd") != nullptr)
		// {
		// 	tchPasswd = std::getenv("tchPasswd");
		// }
		switch (selected)
		{
		case mode::storage:
			if (nickname.empty())
			{
				std::cout << "Error: nickname is neccessary." << std::endl;
				break;
			}
			else
			{
				std::cout << db_manager::get_json_data_from_db(nickname) << std::endl;
			}
			break;
		case mode::read:
			if (nickname.empty())
			{
				std::cout << "Error: nickname is neccessary." << std::endl;
				break;
			}
			else
			{
				// TODO: 2;
			}
			break;
		case mode::generate:
			// TODO: generate;
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
