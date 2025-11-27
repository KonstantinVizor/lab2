#include <cassert>
#include "../../inc/controllers/hotel/DeleteByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockHotelRepository.h"

int main(void)
{
	std::shared_ptr<HotelRepository> rep = std::make_shared<MockHotelRepository>();
	MockResponse resp;
	MockRequest req;
	Hotel::DeleteByUidController controller(rep);
	req.setURI("/hotel?hotel_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	return 0;
}
