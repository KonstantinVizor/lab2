#include <cassert>
#include "../../inc/controllers/loyalty/GetAllController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockLoyaltyRepository.h"
#include "../util/JsonToVectorConverter.h"

int main(void)
{
	std::shared_ptr<LoyaltyRepository> rep = std::make_shared<MockLoyaltyRepository>();
	std::vector<LoyaltyModel> testData;
	testData.push_back(LoyaltyModel().setId(0)
					.setUsername("Kostya")
					.setReservationCount(10)
					.setStatus(LoyaltyModel::Status::GOLD)
					.setDiscont(10));
	testData.push_back(LoyaltyModel().setId(1)
					.setUsername("Miha")
					.setReservationCount(20)
					.setStatus(LoyaltyModel::Status::BRONZE)
					.setDiscont(20));
	JsonVectorConverter converter;
	MockResponse resp;
	MockRequest req;
	static_cast<MockLoyaltyRepository *>(rep.get())->setTestData(testData);
	Loyalty::GetAllController controller(rep);

	controller.handleRequest(req, resp);
	
	std::string json = resp.getStream().str();
	std::vector<std::string> jsons = converter.jsonToVector(json);
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(jsons.size() == testData.size());
	for (int i = 0; i < static_cast<int>(jsons.size()); i++)
	{
		LoyaltyModel tmp;
		tmp.fromJson(jsons[i]);
		assert(tmp == testData[i]);
	}
	return 0;
}
