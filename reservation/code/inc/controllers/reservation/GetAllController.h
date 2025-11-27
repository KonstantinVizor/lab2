#ifndef __RESERVATIONGETALLCONTROLLER_H__
#define __RESERVATIONGETALLCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../repositories/ReservationRepository.h"

namespace Reservation
{
// not used
class GetAllController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<ReservationRepository> _reservationRepository;

	public:
		GetAllController() = default;
		explicit GetAllController(const GetAllController &) = delete;
		GetAllController(GetAllController &&) = delete;
		~GetAllController() = default;

		GetAllController(const std::shared_ptr<ReservationRepository> &reservationRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
