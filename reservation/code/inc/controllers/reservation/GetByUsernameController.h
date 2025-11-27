#ifndef __RESERVATIONGETBYUSERNAMECONTROLLER_H__
#define __RESERVATIONGETBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/ReservationRepository.h"
#include "../../../inc/repositories/HotelRepository.h"

namespace Reservation
{
class GetByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<ReservationRepository> _reservationRepository;
		std::shared_ptr<HotelRepository> _hotelRepository;

	public:
		GetByUsernameController() = default;
		explicit GetByUsernameController(const GetByUsernameController &) = delete;
		GetByUsernameController(GetByUsernameController &&) = delete;
		~GetByUsernameController() = default;
	
		GetByUsernameController(const std::shared_ptr<ReservationRepository> &reservationRepository,
					const std::shared_ptr<HotelRepository> &hotelRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
