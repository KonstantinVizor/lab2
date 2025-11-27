#include <cassert>
#include "../../inc/controllers/loyalty/UpdateByUsernameController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockLoyaltyRepository.h"

int main(void)
{
	std::shared_ptr<LoyaltyRepository> rep = std::make_shared<MockLoyaltyRepository>();
	LoyaltyModel testData, resData;
	testData.setId(0)
		.setUsername("Kostya")
		.setReservationCount(10)
		.setStatus(LoyaltyModel::Status::GOLD)
		.setDiscont(10);
	resData.setId(0)
		.setUsername("Miha")
		.setReservationCount(20)
		.setStatus(LoyaltyModel::Status::GOLD)
		.setDiscont(10);
	std::string updateJson = "{\"username\":\"Miha\",\"reservationCount\":20}";
	MockResponse resp;
	Loyalty::UpdateByUsernameController controller(rep);
	static_cast<MockLoyaltyRepository *>(rep.get())->setTestData(testData);
	MockRequest req(updateJson);
	req.setURI("/loyalty");
	req.set("X-User-Name", "Kostya");

	controller.handleRequest(req, resp);
	
	LoyaltyModel tmp1, tmp2;
	tmp1.fromJson(resp.getStream().str());
	tmp2 = rep->getByUsername(resData.getUsername()).value();
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(tmp1 == tmp2);
	assert(tmp1 == resData);
	return 0;
}
