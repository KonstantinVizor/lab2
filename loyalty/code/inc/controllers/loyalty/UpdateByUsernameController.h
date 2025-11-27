#ifndef __LOYALITYUPDATEBYUSERNAMECONTROLLER_H__
#define __LOYALITYUPDATEBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/LoyaltyRepository.h"

namespace Loyalty
{
class UpdateByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		UpdateByUsernameController() = default;
		explicit UpdateByUsernameController(const UpdateByUsernameController &) = delete;
		UpdateByUsernameController(UpdateByUsernameController &&) = delete;
		~UpdateByUsernameController() = default;
	
		UpdateByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
