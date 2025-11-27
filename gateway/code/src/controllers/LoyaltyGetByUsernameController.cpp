#include "../../inc/controllers/LoyaltyGetByUsernameController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../inc/models/LoyaltyInfo.h"

LoyaltyGetByUsernameController::LoyaltyGetByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository) :
												Poco::Net::HTTPRequestHandler(),
												_loyaltyRepository(loyaltyRepository)
{}

void LoyaltyGetByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	std::string username = req.get("X-User-Name");
	LoyaltyInfo result = _loyaltyRepository->getByUsername(username);
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.send() << result.toJson();
}
