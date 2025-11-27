#include <cassert>
#include "../../inc/controllers/hotel/CreateController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockHotelRepository.h"

int main(void)
{
	HotelResponce testData;
	testData.setId(0)
		.setHotelUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setName("Plasa")
		.setCountry("Russia")
		.setCity("Moscow")
		.setAddress("Street")
		.setStars(5)
		.setPrice(100);
	std::string json = testData.toJson();
	MockResponse resp;
	std::shared_ptr<HotelRepository> rep = std::make_shared<MockHotelRepository>();
	Hotel::CreateController controller(rep);
	MockRequest req(json);
	static_cast<MockHotelRepository *>(rep.get())->setUid("f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
	assert(resp.get("location") == "/hotel?hotel_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");
	return 0;
}
