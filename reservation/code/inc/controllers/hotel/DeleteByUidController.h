#ifndef __HOTELDELETEBYUIDCONTROLLER_H__
#define __HOTELDELETEBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/HotelRepository.h"

namespace Hotel
{
// not used
class DeleteByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		DeleteByUidController() = default;
		explicit DeleteByUidController(const DeleteByUidController &) = delete;
		DeleteByUidController(DeleteByUidController &&) = delete;
		~DeleteByUidController() = default;
	
		DeleteByUidController(const std::shared_ptr<HotelRepository> &hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
