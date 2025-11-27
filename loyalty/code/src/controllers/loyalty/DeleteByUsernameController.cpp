#include "../../../inc/controllers/loyalty/DeleteByUsernameController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Loyalty::DeleteByUsernameController::DeleteByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository) :
												Poco::Net::HTTPRequestHandler(),
												_loyaltyRepository(loyaltyRepository)
{}

void Loyalty::DeleteByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::string username = uri.getValue("username");
	_loyaltyRepository->deleteByUsername(username);
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	resp.setContentType("application/json");
	resp.setReason("No Content");
	resp.send() << "{\"message\":\"Person was removed with username = " << username << "\"}";
}
