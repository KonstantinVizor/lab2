#include "../../../inc/controllers/reservation/DeleteByUidController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include "../../../inc/uri/Uri.h"
#include "Poco/Net/HTTPResponse.h"

Reservation::DeleteByUidController::DeleteByUidController(const std::shared_ptr<ReservationRepository> &reservationRepository) :
												Poco::Net::HTTPRequestHandler(),
												_reservationRepository(reservationRepository)
{}

void Reservation::DeleteByUidController::handleRequest(Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	Uri uri(req.getURI());
	std::string uid = uri.getValue("reservation_uid");
	_reservationRepository->deleteByUid(uid);
	resp.setStatus(Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	resp.setContentType("application/json");
	resp.setReason("No Content");
	resp.send() << "{\"message\":\"Reservarion was removed with reservation_uid = " << uid << "\"}";
}
