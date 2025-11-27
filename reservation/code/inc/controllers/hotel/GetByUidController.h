#ifndef __HOTELGETBYUIDCONTROLLER_H__
#define __HOTELGETBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/HotelRepository.h"

namespace Hotel
{
class GetByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		GetByUidController() = default;
		explicit GetByUidController(const GetByUidController &) = delete;
		GetByUidController(GetByUidController &&) = delete;
		~GetByUidController() = default;
	
		GetByUidController(const std::shared_ptr<HotelRepository> &hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
