#include <cassert>
#include "../../inc/controllers/loyalty/CreateController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockLoyaltyRepository.h"

int main(void)
{
	LoyaltyModel testData;
	testData.setId(0)
		.setUsername("Kostya")
		.setReservationCount(40)
		.setStatus(LoyaltyModel::Status::BRONZE)
		.setDiscont(10);
	std::string json = testData.toJson();
	MockResponse resp;
	std::shared_ptr<LoyaltyRepository> rep = std::make_shared<MockLoyaltyRepository>();
	Loyalty::CreateController controller(rep);
	MockRequest req(json);
	static_cast<MockLoyaltyRepository *>(rep.get())->setId(12);

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
	assert(resp.get("location") == "/loyalty?username=Kostya");
	return 0;
}
