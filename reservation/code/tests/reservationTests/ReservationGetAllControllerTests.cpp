#include <cassert>
#include <ctime>
#include "../../inc/controllers/reservation/GetAllController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockReservationRepository.h"
#include "../util/JsonToVectorConverter.h"

int main(void)
{
	std::shared_ptr<ReservationRepository> rep = std::make_shared<MockReservationRepository>();
	std::vector<ReservationModel> testData;
	std::time_t now = std::time(nullptr);
	uint32_t secsPerYear = 31536000;
	testData.push_back(ReservationModel().setId(0)
					.setReservationUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
					.setUsername("kvizor")
					.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
					.setHotelId(1)
					.setStatus(ReservationModel::Status::PAID)
					.setStartDate(now)
					.setEndDate(now + secsPerYear));
	testData.push_back(ReservationModel().setId(1)
					.setReservationUid("f47ac10b-58cc-4372-a567-0e02b2c3d472")
					.setUsername("kvizor")
					.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
					.setHotelId(3)
					.setStatus(ReservationModel::Status::CANCELED)
					.setStartDate(now)
					.setEndDate(now + secsPerYear));
	JsonVectorConverter converter;
	MockResponse resp;
	MockRequest req;
	static_cast<MockReservationRepository *>(rep.get())->setTestData(testData);
	Reservation::GetAllController controller(rep);

	controller.handleRequest(req, resp);
	
	std::string json = resp.getStream().str();
	std::vector<std::string> jsons = converter.jsonToVector(json);
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(jsons.size() == testData.size());
	for (int i = 0; i < static_cast<int>(jsons.size()); i++)
	{
		ReservationModel tmp;
		tmp.fromJson(jsons[i]);
		assert(tmp == testData[i]);
	}
	return 0;
}
