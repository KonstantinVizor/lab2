#ifndef __RESERVATIONGETBYUSERNAMENUIDCONTROLLER_H__
#define __RESERVATIONGETBYUSERNAMENUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../inc/repositories/HotelRepository.h"
#include "../../inc/repositories/PaymentRepository.h"

class ReservationGetByUsernameNUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		ReservationGetByUsernameNUidController() = default;
		explicit ReservationGetByUsernameNUidController(const ReservationGetByUsernameNUidController &) = delete;
		ReservationGetByUsernameNUidController(ReservationGetByUsernameNUidController &&) = delete;
		~ReservationGetByUsernameNUidController() = default;
	
		ReservationGetByUsernameNUidController(const std::shared_ptr<HotelRepository> &reservationRepository, 
							const std::shared_ptr<PaymentRepository> &paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
