#ifndef __MEGETBYUSERNAMECONTROLLER_H__
#define __MEGETBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../inc/repositories/HotelRepository.h"
#include "../../inc/repositories/LoyaltyRepository.h"
#include "../../inc/repositories/PaymentRepository.h"

class MeGetByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<HotelRepository> _hotelRepository;
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		MeGetByUsernameController() = default;
		explicit MeGetByUsernameController(const MeGetByUsernameController &) = delete;
		MeGetByUsernameController(MeGetByUsernameController &&) = delete;
		~MeGetByUsernameController() = default;
	
		MeGetByUsernameController(const std::shared_ptr<HotelRepository> &hotelRepository,
					const std::shared_ptr<LoyaltyRepository> &loyaltyRepository,
					const std::shared_ptr<PaymentRepository> &paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
