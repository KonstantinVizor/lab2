#include "../../inc/controllerFactory/ControllerFactory.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <regex>

ControllerFactory::ControllerFactory()
{
	_regexMap = {{R"((\d{1,}))", std::regex(R"(\{i\})")}};
}

ControllerFactory& ControllerFactory::registerHandler(const std::string &path, const std::string &method,
							const HandlerCreator &creator)
{
	std::string resultPath = path;
	for (RegexMap::value_type &pair : _regexMap)
		resultPath = std::regex_replace(resultPath, pair.second, pair.first);
	_creators.push_back({resultPath, method, creator});
	return *this;
}

ControllerFactory& ControllerFactory::registerDefaultHandler(const HandlerCreator &creator)
{
	_defaultCreator = creator;
	return *this;
}

#include <iostream>

ControllerFactory::HandlerPtr ControllerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest &req)
{
	bool found = false;
	HandlerPtr result = nullptr;
	std::string path = "";
	for (int i = 0; i < static_cast<int>(req.getURI().size()) &&
			req.getURI()[i] != '?' && req.getURI()[i] != '#'; i++)
		path += req.getURI()[i];
	for (HandlerCreatorMap::value_type tuple : _creators)
	{
		if (std::regex_match(path, std::regex(std::get<0>(tuple))) &&
				req.getMethod() == std::get<1>(tuple))
		{
			found = true;
			result = std::get<2>(tuple)();
		}
	}
	if (!found)
		result = _defaultCreator();
	return result;
}
