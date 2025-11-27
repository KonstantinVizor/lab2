#include "../../../inc/controllers/loyalty/UpdateByUsernameController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <algorithm>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Loyalty::UpdateByUsernameController::UpdateByUsernameController(const std::shared_ptr<LoyaltyRepository> loyaltyRepository) :
												Poco::Net::HTTPRequestHandler(),
												_loyaltyRepository(loyaltyRepository)
{}

void Loyalty::UpdateByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	Uri uri(req.getURI());
	std::optional<LoyaltyModel> model;
	std::string username = req.get("X-User-Name");//uri.getValue("username");
	std::string body = "", tmp;
	while (req.stream() >> tmp)
	{
		body += (tmp + ' ');
	}
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
		correctJson = model->fromJson(body, false);
		if (correctJson)
		{
			_loyaltyRepository->updateByUsername(username, *model);
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
			resp.setContentType("application/json");
			resp.send() << model->toJson();
		}
		else
		{
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
			resp.setReason("Bad Request");
			resp.send() << "{\"message\":\"request's json is invalid\"}";
		}
	}
	else
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setContentType("application/json");
		resp.setReason("Not Found");
		resp.send() << "{\"message\":\"Cannot find person with username = " << username << "\"}";
	}
}
