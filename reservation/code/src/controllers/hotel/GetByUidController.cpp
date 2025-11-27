#include "../../../inc/controllers/hotel/GetByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Hotel::GetByUidController::GetByUidController(const std::shared_ptr<HotelRepository> &hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_hotelRepository(hotelRepository)
{}

void Hotel::GetByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::optional<HotelResponce> model;
	std::string uid = uri.getValue("hotel_uid");
	if (uid == "")
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
		resp.setReason("No Content");
		resp.send();
		return;
	}
	model = _hotelRepository->getByUid(uid);
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
		resp.send() << "{\"message\":\"Cannot find hotel with hotel_uid = " << uid << "\"}";
	}
}
