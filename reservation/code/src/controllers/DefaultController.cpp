#include "../../inc/controllers/DefaultController.h"
#include "Poco/Net/HTTPServerResponse.h"

void DefaultController::handleRequest([[maybe_unused]] Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_NOT_FOUND);
	resp.setReason("Not Found");
	resp.send() << "Page Not Found 404";
}
