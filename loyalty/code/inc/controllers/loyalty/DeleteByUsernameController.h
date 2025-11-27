#ifndef __LOYALITYDELETEBYUSERNAMECONTROLLER_H__
#define __LOYALITYDELETEBYUSERNAMECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/LoyaltyRepository.h"

namespace Loyalty
{
// not used
class DeleteByUsernameController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		DeleteByUsernameController() = default;
		explicit DeleteByUsernameController(const DeleteByUsernameController &) = delete;
		DeleteByUsernameController(DeleteByUsernameController &&) = delete;
		~DeleteByUsernameController() = default;
	
		DeleteByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
