#ifndef __RESERVATIONCREATEBYUSERNAMECONTROLLER_H__
#define __RESERVATIONCREATEBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../inc/repositories/HotelRepository.h"
#include "../../inc/repositories/PaymentRepository.h"
#include "../../inc/repositories/LoyaltyRepository.h"

class ReservationCreateByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;
		std::shared_ptr<PaymentRepository> _paymentRepository;
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		ReservationCreateByUsernameController() = default;
		explicit ReservationCreateByUsernameController(const ReservationCreateByUsernameController &) = delete;
		ReservationCreateByUsernameController(ReservationCreateByUsernameController &&) = delete;
		~ReservationCreateByUsernameController() = default;
	
		ReservationCreateByUsernameController(const std::shared_ptr<HotelRepository> &hotelRepository, 
							const std::shared_ptr<PaymentRepository> &paymentRepository,
							const std::shared_ptr<LoyaltyRepository> &loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
