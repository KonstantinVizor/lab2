#include "../../inc/controllers/MeGetByUsernameController.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "Poco/Net/HTTPRequestHandler.h"
#include "../../inc/models/ReservationResponse.h"
#include "../../inc/models/ReservationWithHotel.h"
#include "../../inc/models/LoyaltyInfo.h"
#include "../../inc/models/PaymentInfo.h"
#include "../../inc/models/UserInfoResponse.h"
#include <vector>

MeGetByUsernameController::MeGetByUsernameController(const std::shared_ptr<HotelRepository> &hotelRepository,
							const std::shared_ptr<LoyaltyRepository> &loyaltyRepository,
							const std::shared_ptr<PaymentRepository> &paymentRepository) :
												Poco::Net::HTTPRequestHandler(),
												_hotelRepository(hotelRepository),
												_loyaltyRepository(loyaltyRepository),
												_paymentRepository(paymentRepository)
{}

void MeGetByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	std::string username = req.get("X-User-Name");
	std::vector<ReservationWithHotel> reservations = _hotelRepository->getReservationsByUsername(username);
	std::vector<ReservationResponse> ress;
	PaymentInfo payment;
	UserInfoResponse result;
	LoyaltyInfo loyalty = _loyaltyRepository->getByUsername(username);
	for (ReservationWithHotel &reservation : reservations)
	{
		payment = _paymentRepository->getByUid(reservation.getPaymentUid());
		ress.push_back(ReservationResponse().setEndDate(reservation.getEndDate())
							.setHotel(reservation.getHotel())
							.setStatus(reservation.getStatus())
							.setPayment(payment)
							.setStartDate(reservation.getStartDate())
							.setReservationUid(reservation.getReservationUid()));
	}
	result.setReservations(ress)
		.setLoyalty(loyalty);
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.send() << result.toJson();
}
