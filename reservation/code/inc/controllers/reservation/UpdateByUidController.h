#ifndef __RESERVATIONUPDATEBYUIDCONTROLLER_H__
#define __RESERVATIONUPDATEBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/ReservationRepository.h"

namespace Reservation
{
class UpdateByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<ReservationRepository> _reservationRepository;

	public:
		UpdateByUidController() = default;
		explicit UpdateByUidController(const UpdateByUidController &) = delete;
		UpdateByUidController(UpdateByUidController &&) = delete;
		~UpdateByUidController() = default;
	
		UpdateByUidController(const std::shared_ptr<ReservationRepository> &reservationRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
