#ifndef __LOYALTYGETBYUSERNAMECONTROLLER_H__
#define __LOYALTYGETBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../inc/repositories/LoyaltyRepository.h"

class LoyaltyGetByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		LoyaltyGetByUsernameController() = default;
		explicit LoyaltyGetByUsernameController(const LoyaltyGetByUsernameController &) = delete;
		LoyaltyGetByUsernameController(LoyaltyGetByUsernameController &&) = delete;
		~LoyaltyGetByUsernameController() = default;
	
		LoyaltyGetByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};

#endif
