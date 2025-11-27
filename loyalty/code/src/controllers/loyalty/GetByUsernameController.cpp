#include "../../../inc/controllers/loyalty/GetByUsernameController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Loyalty::GetByUsernameController::GetByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository) :
												Poco::Net::HTTPRequestHandler(),
												_loyaltyRepository(loyaltyRepository)
{}

void Loyalty::GetByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::optional<LoyaltyModel> model;
	std::string username = req.get("X-User-Name");
	if (username == "")
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
		resp.setReason("No Content");
		resp.send();
		return;
	}
	model = _loyaltyRepository->getByUsername(username);
	if (model.has_value())
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
		resp.setContentType("application/json");
		resp.send() << model->toJson();
	}
	else
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setContentType("application/json");
		resp.setReason("Not Found");
		resp.send() << "{\"message\":\"Cannot find person with username = " << username << "\"}";
	}
}
