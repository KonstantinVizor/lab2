#ifndef __LOYALITYGETALLCONTROLLER_H__
#define __LOYALITYGETALLCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../repositories/LoyaltyRepository.h"

namespace Loyalty
{
// not used
class GetAllController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<LoyaltyRepository> _loyaltyRepository;

	public:
		GetAllController() = default;
		explicit GetAllController(const GetAllController &) = delete;
		GetAllController(GetAllController &&) = delete;
		~GetAllController() = default;

		GetAllController(const std::shared_ptr<LoyaltyRepository> &loyaltyRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
