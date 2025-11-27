#ifndef __RESERVATIONGETBYUSERNAMECONTROLLER_H__
#define __RESERVATIONGETBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../inc/repositories/HotelRepository.h"
#include "../../inc/repositories/PaymentRepository.h"

class ReservationGetByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		ReservationGetByUsernameController() = default;
		explicit ReservationGetByUsernameController(const ReservationGetByUsernameController &) = delete;
		ReservationGetByUsernameController(ReservationGetByUsernameController &&) = delete;
		~ReservationGetByUsernameController() = default;
	
		ReservationGetByUsernameController(const std::shared_ptr<HotelRepository> &reservationRepository, 
							const std::shared_ptr<PaymentRepository> &paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
