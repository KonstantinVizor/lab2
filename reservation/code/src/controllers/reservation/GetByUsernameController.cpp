#include "../../../inc/controllers/reservation/GetByUsernameController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>
#include "../../../inc/uri/Uri.h"
#include "../../../inc/models/ReservationWithHotel.h"
#include "../../../inc/models/HotelInfo.h"

Reservation::GetByUsernameController::GetByUsernameController(const std::shared_ptr<ReservationRepository> &reservationRepository,
								const std::shared_ptr<HotelRepository> &hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_reservationRepository(reservationRepository),
												_hotelRepository(hotelRepository)
{}

void Reservation::GetByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	std::vector<ReservationModel> models;
	std::vector<ReservationWithHotel> results;
	HotelResponce hotel;
	Uri uri(req.getURI());
	std::string username = req.get("X-User-Name"); //uri.getPathFragment(uri.getPathSize() - 1);
	std::string message;
	models = _reservationRepository->getByUsername(username);
	for (uint32_t i = 0; i < models.size(); i++)
	{
		results.push_back(ReservationWithHotel(models[i]));
		hotel = _hotelRepository->getById(models[i].getHotelId()).value();
		results.back().setHotelInfo(HotelInfo(hotel));
	}
	message = "[";
	for (int i = 0; i < static_cast<int>(results.size()); i++)
	{
		message += results[i].toJson();
		if (i != (static_cast<int>(results.size()) - 1))
			message += ",";
	}
	message += "]";
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.sendBuffer(message.data(), message.size());
}
