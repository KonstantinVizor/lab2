#include "../../../inc/controllers/hotel/DeleteByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Hotel::DeleteByUidController::DeleteByUidController(const std::shared_ptr<HotelRepository> &hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_hotelRepository(hotelRepository)
{}

void Hotel::DeleteByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::string uid = uri.getValue("hotel_uid");
	_hotelRepository->deleteByUid(uid);
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	resp.setContentType("application/json");
	resp.setReason("No Content");
	resp.send() << "{\"message\":\"Hotel was removed with hotel_uid = " << uid << "\"}";
}
