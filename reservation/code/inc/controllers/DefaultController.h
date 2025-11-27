#ifndef __DEFAULTCONTROLLER_H__
#define __DEFAULTCONTROLLER_H__

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <Poco/Net/HTTPRequestHandler.h>

class DefaultController : public Poco::Net::HTTPRequestHandler
{
	public:
		DefaultController() = default;
		explicit DefaultController(const DefaultController &) = delete;
		DefaultController(DefaultController &&) = delete;
		~DefaultController() = default;

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
