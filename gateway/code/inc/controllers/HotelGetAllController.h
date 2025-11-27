#ifndef __HOTELGETALLCONTROLLER_H__
#define __HOTELGETALLCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../inc/repositories/HotelRepository.h"

class HotelGetAllController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		HotelGetAllController() = default;
		explicit HotelGetAllController(const HotelGetAllController &) = delete;
		HotelGetAllController(HotelGetAllController &&) = delete;
		~HotelGetAllController() = default;
	
		HotelGetAllController(const std::shared_ptr<HotelRepository> hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
