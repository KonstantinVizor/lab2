#include <cassert>
#include "../../inc/controllers/reservation/DeleteByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockReservationRepository.h"

int main(void)
{
	std::shared_ptr<ReservationRepository> rep = std::make_shared<MockReservationRepository>();
	MockResponse resp;
	MockRequest req;
	Reservation::DeleteByUidController controller(rep);
	req.setURI("/reservation/f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	return 0;
}
