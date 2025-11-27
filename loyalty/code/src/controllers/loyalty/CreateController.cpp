#include "../../../inc/controllers/loyalty/CreateController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <optional>
#include "Poco/Net/HTTPResponse.h"

Loyalty::CreateController::CreateController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository) :
												Poco::Net::HTTPRequestHandler(),
												_loyaltyRepository(loyaltyRepository)
{}

void Loyalty::CreateController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	std::string uuid;
	LoyaltyModel model;
	std::string body = "", tmp;
	while (req.stream() >> tmp)
		body += (tmp + " ");
	correctJson = model.fromJson(body, true);
	if (!correctJson)
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
		resp.setReason("Bad Request");
		resp.send() << "{\"message\":\"request's json is invalid\"}";
	}
	else
	{
		std::optional<LoyaltyModel> tmpModel = _loyaltyRepository->getByUsername(model.getUsername());
		if (tmpModel.has_value())
		{
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
			resp.setReason("Bad Request");
			resp.send() << "{\"message\":\"username already exist\"}";
		}
		else
		{
			_loyaltyRepository->create(model);
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
			resp.setReason("Created");
			resp.add("location", "/loyalty?username=" + model.getUsername());
			resp.send();
		}
	}
}
