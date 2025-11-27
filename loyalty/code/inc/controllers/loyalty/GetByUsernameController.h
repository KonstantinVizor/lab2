#ifndef __LOYALITYGETBYUSERNAMECONTROLLER_H__
#define __LOYALITYGETBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/LoyaltyRepository.h"

namespace Loyalty
{
class GetByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		GetByUsernameController() = default;
		explicit GetByUsernameController(const GetByUsernameController &) = delete;
		GetByUsernameController(GetByUsernameController &&) = delete;
		~GetByUsernameController() = default;
	
		GetByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
