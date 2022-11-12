#include "json_manager.hpp"

namespace json_manager
{
	std::string format_json(std::string input_json)
	{
		Json::CharReaderBuilder readerBuilder;
		JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;

		if (reader->parse(input_json.data(), input_json.data() + input_json.size(), &root, &errs))
		{
			return root.toStyledString();
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}
}
