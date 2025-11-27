#include <cassert>
#include "../../inc/controllers/hotel/GetByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockHotelRepository.h"
#include <Poco/Net/HTTPResponse.h>

int main(void)
{
	std::shared_ptr<HotelRepository> rep = std::make_shared<MockHotelRepository>();
	HotelResponce testData;
	testData.setId(0)
		.setHotelUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setName("Plasa")
		.setCountry("Russia")
		.setCity("Moscow")
		.setAddress("Street")
		.setStars(5)
		.setPrice(100);
	MockResponse resp;
	MockRequest req;
	static_cast<MockHotelRepository *>(rep.get())->setTestData(testData);
	bool flag;
	Hotel::GetByUidController controller(rep);
	req.setURI("/hotel?hotel_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	HotelResponce tmp;
	std::string json = resp.getStream().str();
	flag = tmp.fromJson(json);
	assert(flag);
	assert(tmp == testData);

	
	req.setURI("/hotel?hotel_uid=f47ac10b-58cc-4372-a567-0e02b2c3d434");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
	return 0;
}
