#include "../../../inc/controllers/payment/GetByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <optional>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Payment::GetByUidController::GetByUidController(const std::shared_ptr<PaymentRepository> paymentRepository) :
												Poco::Net::HTTPRequestHandler(),
												_paymentRepository(paymentRepository)
{}

void Payment::GetByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::optional<PaymentModel> model;
	std::string uid = uri.getValue("payment_uid");
	if (uid == "")
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
		resp.setReason("No Content");
		resp.send();
		return;
	}
	model = _paymentRepository->getByUid(uid);
	if (model.has_value())
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
		resp.setContentType("application/json");
		resp.send() << model->toJson();
	}
	else
	{
		resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
		resp.setContentType("application/json");
		resp.setReason("Not Found");
		resp.send() << "{\"message\":\"Cannot find person with payment_uid = " << uid << "\"}";
	}
}
