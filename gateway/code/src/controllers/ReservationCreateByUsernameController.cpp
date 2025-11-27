#include "../inc/controllers/ReservationCreateByUsernameController.h"		
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <exception>
#include "../inc/models/CreateReservationRequest.h"
#include "../inc/models/CreateReservationResponse.h"
#include <iostream>
#include <Poco/Net/NetException.h>

ReservationCreateByUsernameController::ReservationCreateByUsernameController(const std::shared_ptr<HotelRepository> &hotelRepository,
										const std::shared_ptr<PaymentRepository> &paymentRepository,
										const std::shared_ptr<LoyaltyRepository> &loyaltyRepository) :
													Poco::Net::HTTPRequestHandler(),
													_hotelRepository(hotelRepository),
													_paymentRepository(paymentRepository),
													_loyaltyRepository(loyaltyRepository)
{}

void ReservationCreateByUsernameController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	std::string json = "";
	std::string tmp;
	std::string username = req.get("X-User-Name");
	std::string uid;
	CreateReservationRequest createReq;
	ReservationWithHotel resresp;
	while (req.stream() >> tmp)
		json += tmp;
	if (!createReq.fromJson(json))
	{
		resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_BAD_REQUEST);
		resp.setReason("Bad Request");
		resp.setContentType("application/json");
		resp.send() << "\"message\": \"string\",\"errors\": [{\"field\": \"string\",\"error\": \"string\"}]}";
	}
	else
	{
		LoyaltyInfo linfo = _loyaltyRepository->getByUsername(username);
		HotelResponce hresp = _hotelRepository->getHotelByUid(createReq.getHotelUid());
//		std::cout << __LINE__ << "\n";
		uint32_t count = (createReq.getEndDate() - createReq.getStartDate()) / (3600 * 24);
		uint32_t sum = count * hresp.getPrice();
		if (linfo.getStatus() == "BRONZE")
			sum *= 0.95;
		else if (linfo.getStatus() == "SILVER")
			sum *= 0.93;
		else
			sum *= 0.9;
		linfo.setReservationCount(linfo.getReservationCount() + 1);
		if (linfo.getReservationCount() > 20)
			linfo.setstatus(LoyaltyInfo::Status::GOLD)
				.setDiscount(10);
		else if (linfo.getReservationCount() > 10)
			linfo.setstatus(LoyaltyInfo::Status::SILVER)
				.setDiscount(7);
		else
			linfo.setDiscount(5);
		_loyaltyRepository->updateByUsername(username, LoyaltyModel().setStatus(linfo.getStatus())
										.setDiscont(linfo.getDiscount())
										.setUsername(username)
										.setReservationCount(linfo.getReservationCount()));
		PaymentModel pModel;
		pModel.setPrice(sum)
			.setStatus(PaymentModel::Status::PAID)
			.setId(0);
		CreateReservationResponse createResp;
		std::string puid = _paymentRepository->create(pModel);
		createReq.setPaymentUid(puid);
		resresp = _hotelRepository->createReservation(username, createReq);
		createResp.setEndDate(resresp.getEndDate())
				.setStatus(resresp.getStatus())
				.setPayment(PaymentInfo().setPrice(sum)
								.setStatus(PaymentInfo::Status::PAID))
				.setDiscount(linfo.getDiscount())
				.setHotelUid(createReq.getHotelUid())
				.setStartDate(resresp.getStartDate())
				.setReservationUid(resresp.getReservationUid());
		resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
		resp.setReason("OK");
		resp.setContentType("application/json");
		resp.send() << createResp.toJson();
	}
}
