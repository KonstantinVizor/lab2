#include <cassert>
#include "../../inc/controllers/loyalty/GetByUsernameController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockLoyaltyRepository.h"
#include <Poco/Net/HTTPResponse.h>

int main(void)
{
	std::shared_ptr<LoyaltyRepository> rep = std::make_shared<MockLoyaltyRepository>();
	LoyaltyModel testData;
	testData.setId(0)
		.setUsername("Kostya")
		.setReservationCount(10)
		.setStatus(LoyaltyModel::Status::GOLD)
		.setDiscont(10);
	MockResponse resp;
	MockRequest req;
	static_cast<MockLoyaltyRepository *>(rep.get())->setTestData(testData);
	bool flag;
	Loyalty::GetByUsernameController controller(rep);
	req.setURI("/loyalty");
	req.add("X-User-Name", "Kostya");

	controller.handleRequest(req, resp);
	
	LoyaltyModel tmp;
	std::string json = resp.getStream().str();
	flag = tmp.fromJson(json);
	assert(flag);
	assert(tmp == testData);

	
	req.set("X-User-Name", "Miha");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
	return 0;
}
