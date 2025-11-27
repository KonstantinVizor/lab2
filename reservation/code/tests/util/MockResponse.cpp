#include "MockResponse.h"

const std::ostringstream& MockResponse::getStream() const
{
return _mockStream;
}

void MockResponse::sendContinue()
{}

std::ostream& MockResponse::send()
{
	return _mockStream;
}

void MockResponse::sendFile([[maybe_unused]] const std::string& path, [[maybe_unused]] const std::string& mediaType)
{}

void MockResponse::sendBuffer(const void* pBuffer, std::size_t length)
{
	for (int i = 0; i < static_cast<int>(length); i++)
		_mockStream << *(static_cast<const char *>(pBuffer) + i);
}

void MockResponse::redirect([[maybe_unused]] const std::string& uri, [[maybe_unused]] HTTPStatus status)
{}

void MockResponse::requireAuthentication([[maybe_unused]] const std::string& realm)
{}

bool MockResponse::sent() const
{
	return true;
}
