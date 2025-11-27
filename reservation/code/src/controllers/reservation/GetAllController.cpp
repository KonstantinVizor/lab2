#include "../../../inc/controllers/reservation/GetAllController.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

Reservation::GetAllController::GetAllController(const std::shared_ptr<ReservationRepository> &reservationRepository) :
											Poco::Net::HTTPRequestHandler(),
											_reservationRepository(reservationRepository)
{}

void Reservation::GetAllController::handleRequest([[maybe_unused]] Poco::Net::HTTPServerRequest &req, Poco::Net::HTTPServerResponse &resp)
{
	std::vector<ReservationModel> models;
	std::string message;
	models = _reservationRepository->getAll();
	message = "[";
	for (int i = 0; i < static_cast<int>(models.size()); i++)
	{
		message += models[i].toJson();
		if (i != (static_cast<int>(models.size()) - 1))
			message += ",";
	}
	message += "]";
	resp.setStatus(Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
	resp.setContentType("application/json");
	resp.sendBuffer(message.data(), message.size());
}
