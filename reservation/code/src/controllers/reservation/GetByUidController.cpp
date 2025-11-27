#include "../../../inc/controllers/reservation/GetByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "../../../inc/models/ReservationWithHotel.h"

Reservation::GetByUidController::GetByUidController(const std::shared_ptr<ReservationRepository> &reservationRepository,
							const std::shared_ptr<HotelRepository> &hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_reservationRepository(reservationRepository),
												_hotelRepository(hotelRepository)
{}

void Reservation::GetByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::optional<ReservationModel> model;
	ReservationWithHotel result;
	HotelResponce hotel;
	std::string uid = uri.getPathFragment(uri.getPathSize() - 1);
	if (uid == "")
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
		resp.setReason("No Content");
		resp.send();
		return;
	}
	model = _reservationRepository->getByUid(uid);
	if (model.has_value())
	{
		result = ReservationWithHotel(model.value());
		hotel = _hotelRepository->getById(model->getHotelId()).value();
		result.setHotelInfo(HotelInfo(hotel));
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
		resp.setContentType("application/json");
		resp.send() << result.toJson();
	}
	else
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setContentType("application/json");
		resp.setReason("Not Found");
		resp.send() << "{\"message\":\"Cannot find reservation with reservation_uid = " << uid << "\"}";
	}
}
