#ifndef __HOTELUPDATEBYUIDCONTROLLER_H__
#define __HOTELUPDATEBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/HotelRepository.h"

namespace Hotel
{
// not used
class UpdateByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		UpdateByUidController() = default;
		explicit UpdateByUidController(const UpdateByUidController &) = delete;
		UpdateByUidController(UpdateByUidController &&) = delete;
		~UpdateByUidController() = default;
	
		UpdateByUidController(const std::shared_ptr<HotelRepository> &hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
