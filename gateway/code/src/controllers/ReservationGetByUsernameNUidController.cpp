#include "../../inc/controllers/ReservationGetByUsernameNUidController.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include "../../inc/models/ReservationWithHotel.h"
#include "../../inc/models/ReservationResponse.h"
#include "../../inc/uri/Uri.h"

ReservationGetByUsernameNUidController::ReservationGetByUsernameNUidController(const std::shared_ptr<HotelRepository> &hotelRepository,
									const std::shared_ptr<PaymentRepository> &paymentRepository) :
														Poco::Net::HTTPRequestHandler(),
														_hotelRepository(hotelRepository),
														_paymentRepository(paymentRepository)
{}

void ReservationGetByUsernameNUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::string username = req.get("X-User-Name");
	std::string uid = uri.getPathFragment(uri.getPathSize() - 1);
	std::vector<ReservationWithHotel> reservations = _hotelRepository->getReservationsByUsername(username);
	ReservationResponse result;
	PaymentInfo payment;
	bool flag = true;
	for (uint32_t i = 0; flag && i < reservations.size(); i++)
		if (reservations[i].getReservationUid() == uid)
		{
			payment = _paymentRepository->getByUid(reservations[i].getPaymentUid());
			result.setEndDate(reservations[i].getEndDate())
				.setHotel(reservations[i].getHotel())
				.setStatus(reservations[i].getStatus())
				.setPayment(payment)
				.setStartDate(reservations[i].getStartDate())
				.setReservationUid(reservations[i].getReservationUid());
			flag = false;
		}
	if (flag)
	{
		resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setReason("Not Found");
		resp.setContentType("application/json");
		resp.send() << "{\"message\":\"string\"}";
	}
	else
	{
		resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
		resp.setContentType("application/json");
		resp.send() << result.toJson();
	}
}
