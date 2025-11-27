#include <cassert>
#include "../../inc/controllers/hotel/GetAllController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockHotelRepository.h"
#include "../../inc/models/PaginationResponce.h"

int main(void)
{
	std::shared_ptr<HotelRepository> rep = std::make_shared<MockHotelRepository>();
	std::vector<HotelResponce> testData;
	testData.push_back(HotelResponce().setId(0)
			.setHotelUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
			.setName("Plasa")
			.setCountry("Russia")
			.setCity("Moscow")
			.setAddress("Street")
			.setStars(5)
			.setPrice(100));
	testData.push_back(HotelResponce().setId(1)
			.setHotelUid("f47ac10b-58cc-4372-a567-0e02b2c3d473")
			.setName("Blasa")
			.setCountry("Russia")
			.setCity("Moscow")
			.setAddress("Street")
			.setStars(4)
			.setPrice(300));
	MockResponse resp;
	MockRequest req;
	req.setURI("/hotel?page=0&size=2");
	static_cast<MockHotelRepository *>(rep.get())->setTestData(testData);
	Hotel::GetAllController controller(rep);

	controller.handleRequest(req, resp);
	
	std::string json = resp.getStream().str();
	PaginationResponce pagination;
	pagination.fromJson(json);
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(pagination.getHotels().size() == testData.size());
	for (int i = 0; i < static_cast<int>(pagination.getHotels().size()); i++)
		assert(pagination.getHotels()[i] == testData[i]);
	return 0;
}
