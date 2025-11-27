#ifndef __HOTELCREATECONTROLLER_H__
#define __HOTELCREATECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/HotelRepository.h"

namespace Hotel
{
// not used
class CreateController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		CreateController() = default;
		explicit CreateController(const CreateController &) = delete;
		CreateController(CreateController &&) = delete;
		~CreateController() = default;
	
		CreateController(const std::shared_ptr<HotelRepository> &hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
