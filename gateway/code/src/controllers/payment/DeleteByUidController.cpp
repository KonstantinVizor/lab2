#include "../../../inc/controllers/payment/DeleteByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Payment::DeleteByUidController::DeleteByUidController(const std::shared_ptr<PaymentRepository> paymentRepository) :
												Poco::Net::HTTPRequestHandler(),
												_paymentRepository(paymentRepository)
{}

void Payment::DeleteByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::string uid = uri.getValue("payment_uid");
	_paymentRepository->deleteByUid(uid);
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	resp.setContentType("application/json");
	resp.setReason("No Content");
	resp.send() << "{\"message\":\"Person was removed with payment_uid = " << uid << "\"}";
}
