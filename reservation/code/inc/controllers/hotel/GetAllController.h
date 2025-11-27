#ifndef __HOTELGETALLCONTROLLER_H__
#define __HOTELGETALLCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../repositories/HotelRepository.h"

namespace Hotel
{
class GetAllController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		GetAllController() = default;
		explicit GetAllController(const GetAllController &) = delete;
		GetAllController(GetAllController &&) = delete;
		~GetAllController() = default;

		GetAllController(const std::shared_ptr<HotelRepository> &hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
