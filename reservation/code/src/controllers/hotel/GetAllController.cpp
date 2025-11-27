#include "../../../inc/controllers/hotel/GetAllController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <string>
#include "../../../inc/uri/Uri.h"
#include "../../../inc/models/PaginationResponce.h"

Hotel::GetAllController::GetAllController(const std::shared_ptr<HotelRepository> &hotelRepository) :
											Poco::Net::HTTPRequestHandler(),
											_hotelRepository(hotelRepository)
{}

void Hotel::GetAllController::handleRequest([[maybe_unused]] Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	PaginationResponce result;
	Uri uri(req.getURI());
	std::vector<HotelResponce> models;
	std::string message;
	uint32_t pageNumber = std::stoi(uri.getValue("page"));
	uint32_t pageSize = std::stoi(uri.getValue("size"));
	models = _hotelRepository->getAll(pageNumber, pageSize);
	result.setPageNumber(pageNumber)
		.setPageSize(pageSize)
		.setHotels(models);
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.send() << result.toJson();
}
