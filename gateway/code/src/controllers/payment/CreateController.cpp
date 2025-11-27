#include "../../../inc/controllers/payment/CreateController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "Poco/Net/HTTPResponse.h"

Payment::CreateController::CreateController(const std::shared_ptr<PaymentRepository> paymentRepository) :
												Poco::Net::HTTPRequestHandler(),
												_paymentRepository(paymentRepository)
{}

void Payment::CreateController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	bool correctJson;
	PaymentModel model;
	std::string uid;
	std::string body = "", tmp;
	while (req.stream() >> tmp)
		body += (tmp + " ");
	correctJson = model.fromJson(body, true);
	if (!correctJson)
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_BAD_REQUEST);
		resp.setReason("Bad Request");
		resp.send() << "{\"message\":\"request's json is invalid\"}";
	}
	else
	{
		std::tie(std::ignore, uid) = _paymentRepository->create(model);
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
		resp.setReason("Created");
		resp.add("location", "/payment?payment_uid=" + uid);
		resp.send();
	}
}
