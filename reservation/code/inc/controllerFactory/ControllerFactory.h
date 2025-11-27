#ifndef __CONTROLLERFACTORY_H__
#define __CONTROLLERFACTORY_H__

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <functional>
#include <unordered_map>
#include <regex>

class ControllerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
	public:
		using HandlerPtr = Poco::Net::HTTPRequestHandler *;
		using HandlerCreator = std::function<HandlerPtr()>;
		using HandlerCreatorMap = std::vector<std::tuple<std::string,
		      						std::string,
								HandlerCreator>>;
		using RegexMap = std::unordered_map<std::string, std::regex>;

	private:
		HandlerCreator _defaultCreator;
		HandlerCreatorMap _creators;
		RegexMap _regexMap;

	public:
		explicit ControllerFactory(const ControllerFactory &) = delete;
		ControllerFactory(ControllerFactory &&) = delete;
		~ControllerFactory() = default;
		ControllerFactory();
	
		ControllerFactory& registerHandler(const std::string &path, const std::string &method,
							const HandlerCreator &creator);
		ControllerFactory& registerDefaultHandler(const HandlerCreator &creator);

		virtual HandlerPtr createRequestHandler(const Poco::Net::HTTPServerRequest &req) override;
};

#endif
