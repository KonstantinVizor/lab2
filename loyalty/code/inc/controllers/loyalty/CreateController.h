#ifndef __LOYALITYCREATECONTROLLER_H__
#define __LOYALITYCREATECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/LoyaltyRepository.h"

namespace Loyalty
{
// not used
class CreateController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		CreateController() = default;
		explicit CreateController(const CreateController &) = delete;
		CreateController(CreateController &&) = delete;
		~CreateController() = default;
	
		CreateController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
