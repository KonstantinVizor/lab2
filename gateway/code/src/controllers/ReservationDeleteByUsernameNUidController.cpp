#include "../inc/controllers/ReservationDeleteByUsernameNUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include "../inc/models/ReservationWithHotel.h"
#include "../../inc/uri/Uri.h"

ReservationDeleteByUsernameController::ReservationDeleteByUsernameController(const std::shared_ptr<HotelRepository> &hotelRepository,
										const std::shared_ptr<LoyaltyRepository> &loyaltyRepository,
										const std::shared_ptr<PaymentRepository> &paymentRepository) :
															Poco::Net::HTTPRequestHandler(),
															_hotelRepository(hotelRepository),
															_loyaltyRepository(loyaltyRepository),
															_paymentRepository(paymentRepository)
{}

void ReservationDeleteByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::string username = req.get("X-User-Name");
	std::string uid = uri.getPathFragment(uri.getPathSize() - 1);
	std::vector<ReservationWithHotel> reservations = _hotelRepository->getReservationsByUsername(username);
	ReservationWithHotel reservation;
	bool flag = true;
	for (uint32_t i = 0; flag && i < reservations.size(); i++)
		if (reservations[i].getReservationUid() == uid)
		{
			flag = false;
			reservation = reservations[i];
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
		reservation.setStatus(ReservationWithHotel::Status::CANCELED);
		_hotelRepository->updateReservation(uid, reservation);
		LoyaltyInfo linfo = _loyaltyRepository->getByUsername(username);
		if (linfo.getReservationCount() <= 1)
			linfo.setReservationCount(0);
		else
			linfo.setReservationCount(linfo.getReservationCount() - 1);
		if (linfo.getReservationCount() < 10)
			linfo.setstatus(LoyaltyInfo::Status::BRONZE);
		else if (linfo.getReservationCount() < 20)
			linfo.setstatus(LoyaltyInfo::Status::SILVER);
		_loyaltyRepository->updateByUsername(username, LoyaltyModel().setStatus(linfo.getStatus())
										.setDiscont(linfo.getDiscount())
										.setUsername(username)
										.setReservationCount(linfo.getReservationCount()));
		PaymentInfo pinfo = _paymentRepository->getByUid(reservation.getPaymentUid());
		pinfo.setStatus(PaymentInfo::Status::CANCELED);
		_paymentRepository->updateByUid(reservation.getPaymentUid(), PaymentModel().setPrice(pinfo.getPrice())
												.setStatus(pinfo.getStatus())
												.setPaymentUid(reservation.getPaymentUid()));
		resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_NO_CONTENT);
		resp.setReason("No Content");
		resp.send();
	}
}
