#include "../../inc/controllers/HotelGetAllController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "Poco/Net/HTTPResponse.h"
#include "../../inc/uri/Uri.h"

HotelGetAllController::HotelGetAllController(const std::shared_ptr<HotelRepository> hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_hotelRepository(hotelRepository)
{}

void HotelGetAllController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	uint32_t offset, limit;
	Uri uri(req.getURI());
	offset = std::stoi(uri.getValue("page"));
	limit = std::stoi(uri.getValue("size"));
	PaginationResponce result = _hotelRepository->getHotelAll(offset, limit);
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.send() << result.toJson();
}
