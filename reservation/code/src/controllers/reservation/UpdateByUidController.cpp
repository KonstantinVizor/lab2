#include "../../../inc/controllers/reservation/UpdateByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"
#include "../../../inc/models/ReservationWithHotel.h"

Reservation::UpdateByUidController::UpdateByUidController(const std::shared_ptr<ReservationRepository> &reservationRepository) :
												Poco::Net::HTTPRequestHandler(),
												_reservationRepository(reservationRepository)
{}

void Reservation::UpdateByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	Uri uri(req.getURI());
	std::optional<ReservationModel> model;
	ReservationWithHotel rh;
	std::string uid = uri.getValue("reservation_uid");
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
	model = _reservationRepository->getByUid(uid);
	if (model.has_value())
	{
		rh = ReservationWithHotel(model.value());
		correctJson = rh.fromJson(body, false);
		if (correctJson)
		{
			std::optional<ReservationModel> tmpModel = _reservationRepository->getByUid(rh.getReservationUid());
			if (!tmpModel.has_value() || tmpModel->getReservationUid() == rh.getReservationUid())
			{
				_reservationRepository->updateByUid(uid, ReservationModel().setEndDate(rh.getEndDate())
											.setId(model->getId())
											.setStatus(rh.getStatus())
											.setUsername(model->getUsername())
											.setHotelId(model->getHotelId())
											.setStartDate(rh.getStartDate())
											.setPaymentUid(rh.getPaymentUid())
											.setReservationUid(rh.getReservationUid()));
				resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
				resp.setContentType("application/json");
				resp.send() << rh.toJson();
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
		resp.send() << "{\"message\":\"Cannot find reservation with reservation_uid = " << uid << "\"}";
	}
}
