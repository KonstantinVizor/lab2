#ifndef __RESERVATIONDELETEBYUIDCONTROLLER_H__
#define __RESERVATIONDELETEBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/ReservationRepository.h"

namespace Reservation
{
class DeleteByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<ReservationRepository> _reservationRepository;

	public:
		DeleteByUidController() = default;
		explicit DeleteByUidController(const DeleteByUidController &) = delete;
		DeleteByUidController(DeleteByUidController &&) = delete;
		~DeleteByUidController() = default;
	
		DeleteByUidController(const std::shared_ptr<ReservationRepository> &reservationRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
