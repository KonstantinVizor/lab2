#include "../../../inc/controllers/reservation/CreateController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>
#include "../../../inc/models/CreateReservationRequest.h"
#include "../../../inc/models/ReservationWithHotel.h"

Reservation::CreateController::CreateController(const std::shared_ptr<ReservationRepository> &reservationRepository,
						const std::shared_ptr<HotelRepository> &hotelRepository) :
												Poco::Net::HTTPRequestHandler(),
												_reservationRepository(reservationRepository),
												_hotelRepository(hotelRepository)
{}

void Reservation::CreateController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	CreateReservationRequest createJson;
	ReservationModel model;
	ReservationWithHotel result;
	HotelResponce hotel;
	std::string username = req.get("X-User-Name");
	std::string uid;
	std::string body = "", tmp;
	while (req.stream() >> tmp)
		body += (tmp + " ");
	correctJson = createJson.fromJson(body, true);
	if (!correctJson)
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
		resp.setReason("Bad Request");
		resp.send() << "{\"message\":\"request's json is invalid\"}";
		}
	else
	{
			hotel = _hotelRepository->getByUid(createJson.getHotelUid()).value();
			model.setUsername(username)
				.setHotelId(hotel.getId())
				.setStatus(ReservationModel::Status::PAID)
				.setStartDate(createJson.getStartDate())
				.setEndDate(createJson.getEndDate())
				.setPaymentUid(createJson.getPaymentUid());
			std::tie(std::ignore, uid) = _reservationRepository->create(model);
			model = _reservationRepository->getByUid(uid).value();
			result = ReservationWithHotel(model);
			result.setHotelInfo(HotelInfo(hotel));
			resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
		resp.setReason("Created");
			resp.send() << result.toJson();
	}
}
