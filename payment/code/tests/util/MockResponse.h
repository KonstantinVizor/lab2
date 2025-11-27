#ifndef __MOCKRESPONSE_H__
#define __MOCKRESPONSE_H__

#include <ostream>
#include <sstream>
#include <Poco/Net/HTTPServerResponse.h>

class MockResponse : public Poco::Net::HTTPServerResponse
{
	private:
		std::ostringstream _mockStream;

	public:
		const std::ostringstream& getStream() const;
		virtual void sendContinue() override;
		virtual std::ostream& send() override;
		virtual void sendFile(const std::string& path, const std::string& mediaType) override;
		virtual void sendBuffer(const void* pBuffer, std::size_t length) override;
		virtual void redirect(const std::string& uri, HTTPStatus status = HTTP_FOUND) override;
		virtual void requireAuthentication(const std::string& realm) override;
		virtual bool sent() const override;
};

#endif
