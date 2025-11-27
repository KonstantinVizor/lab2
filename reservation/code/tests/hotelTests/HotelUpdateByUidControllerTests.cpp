#include <cassert>
#include "../../inc/controllers/hotel/UpdateByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockHotelRepository.h"

int main(void)
{
	std::shared_ptr<HotelRepository> rep = std::make_shared<MockHotelRepository>();
	HotelResponce testData, resData;
	testData.setId(0)
		.setHotelUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setName("Plasa")
		.setCountry("Russia")
		.setCity("Moscow")
		.setAddress("Street")
		.setStars(5)
		.setPrice(100);
	resData.setId(0)
		.setHotelUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setName("Blasa")
		.setCountry("Russia")
		.setCity("Moscow")
		.setAddress("Street")
		.setStars(4)
		.setPrice(100);
	std::string updateJson = "{\"name\":\"Blasa\",\"stars\":4}";
	MockResponse resp;
	Hotel::UpdateByUidController controller(rep);
	static_cast<MockHotelRepository *>(rep.get())->setTestData(testData);
	MockRequest req(updateJson);
	req.setURI("/hotel?hotel_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	HotelResponce tmp1, tmp2;
	tmp1.fromJson(resp.getStream().str());
	tmp2 = rep->getByUid(resData.getHotelUid()).value();
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(tmp1 == tmp2);
	assert(tmp1 == resData);
	return 0;
}
