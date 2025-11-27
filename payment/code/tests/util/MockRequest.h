#ifndef __MOCKREQUEST_H__
#define __MOCKREQUEST_H__

#include <Poco/Net/HTTPServerRequest.h>
#include <istream>
#include <sstream>

class MockRequest : public Poco::Net::HTTPServerRequest
{
	private:
		std::istringstream _stream;

	public:
		MockRequest() = default;;
		MockRequest(const std::string &json);
		virtual std::istream& stream() override;
		virtual const Poco::Net::SocketAddress& clientAddress() const override;
		virtual const Poco::Net::SocketAddress& serverAddress() const override;
		virtual const Poco::Net::HTTPServerParams& serverParams() const override;
		virtual Poco::Net::HTTPServerResponse& response() const override;
		virtual bool secure() const override;
};

#endif
