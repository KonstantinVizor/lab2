#include "../../inc/controllers/ReservationGetByUsernameController.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include "../../inc/models/ReservationWithHotel.h"
#include "../../inc/models/ReservationResponse.h"

ReservationGetByUsernameController::ReservationGetByUsernameController(const std::shared_ptr<HotelRepository> &hotelRepository,
									const std::shared_ptr<PaymentRepository> &paymentRepository) :
														Poco::Net::HTTPRequestHandler(),
														_hotelRepository(hotelRepository),
														_paymentRepository(paymentRepository)
{}

void ReservationGetByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	std::string username = req.get("X-User-Name");
	std::vector<ReservationWithHotel> reservations = _hotelRepository->getReservationsByUsername(username);
	std::vector<ReservationResponse> ress;
	std::string result;
	PaymentInfo payment;
	result = "[ ";
	for (ReservationWithHotel &reservation : reservations)
	{
		payment = _paymentRepository->getByUid(reservation.getPaymentUid());
		result += ReservationResponse().setEndDate(reservation.getEndDate())
							.setHotel(reservation.getHotel())
							.setStatus(reservation.getStatus())
							.setPayment(payment)
							.setStartDate(reservation.getStartDate())
							.setReservationUid(reservation.getReservationUid())
							.toJson();
		result += ",";
	}
	result[result.size() - 1] = ']';
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.send() << result;
}
