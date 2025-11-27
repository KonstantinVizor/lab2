#include <cassert>
#include "../../inc/controllers/reservation/UpdateByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockReservationRepository.h"

int main(void)
{
	std::shared_ptr<ReservationRepository> rep = std::make_shared<MockReservationRepository>();
	std::time_t now = std::time(nullptr);
	uint32_t secsPerYear = 31536000;
	ReservationModel testData, resData;
	testData.setId(0)
		.setReservationUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setUsername("kvizor")
		.setReservationUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setHotelId(1)
		.setStatus(ReservationModel::Status::PAID)
		.setStartDate(now)
		.setEndDate(now + secsPerYear);
	resData.setId(0)
		.setReservationUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setUsername("kvizor")
		.setReservationUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setHotelId(2)
		.setStatus(ReservationModel::Status::CANCELED)
		.setStartDate(now)
		.setEndDate(now + secsPerYear);
	std::string updateJson = "{\"status\":\"CANCELES\",\"hotel_id\":2}";
	MockResponse resp;
	Reservation::UpdateByUidController controller(rep);
	static_cast<MockReservationRepository *>(rep.get())->setTestData(testData);
	MockRequest req(updateJson);
	req.setURI("/reservation?reservation_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	ReservationModel tmp1, tmp2;
	tmp1.fromJson(resp.getStream().str());
	tmp2 = rep->getByUid(resData.getReservationUid()).value();
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(tmp1 == tmp2);
	assert(tmp1 == resData);
	return 0;
}
