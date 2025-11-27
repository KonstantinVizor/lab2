#include "../../../inc/controllers/hotel/UpdateByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Hotel::UpdateByUidController::UpdateByUidController(const std::shared_ptr<HotelRepository> &hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_hotelRepository(hotelRepository)
{}

void Hotel::UpdateByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	Uri uri(req.getURI());
	std::optional<HotelResponce> model;
	std::string uid = uri.getValue("hotel_uid");
	std::string body = "", tmp;
	while (req.stream() >> tmp)
		body += (tmp + " ");
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
		correctJson = model->fromJson(body, false);
		if (correctJson)
		{
			std::optional<HotelResponce> tmpModel = _hotelRepository->getByUid(model->getHotelUid());
			if (!tmpModel.has_value() || tmpModel->getId() == model->getId())
			{
				_hotelRepository->updateByUid(uid, *model);
				resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
				resp.setContentType("application/json");
				resp.send() << model->toJson();
			}
			else
			{
				resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
				resp.setReason("Bad Request");
				resp.send() << "{\"message\":\"uid already exist\"}";
			}
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
		resp.send() << "{\"message\":\"Cannot find hotel with hotel_uid = " << uid << "\"}";
	}
}
