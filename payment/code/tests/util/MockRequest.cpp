#include "MockRequest.h"

MockRequest::MockRequest(const std::string &json) :
			_stream(json)
{}

std::istream& MockRequest::stream()
{
	return _stream;
}

const Poco::Net::SocketAddress& MockRequest::clientAddress() const
{}

const Poco::Net::SocketAddress& MockRequest::serverAddress() const
{}

const Poco::Net::HTTPServerParams& MockRequest::serverParams() const
{}

Poco::Net::HTTPServerResponse& MockRequest::response() const
{}

bool MockRequest::secure() const
{
	return true;
}
