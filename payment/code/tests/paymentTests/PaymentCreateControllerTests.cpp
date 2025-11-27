#include <cassert>
#include "../../inc/controllers/payment/CreateController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPaymentRepository.h"

int main(void)
{
	PaymentModel testData;
	testData.setId(0)
		.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setStatus(PaymentModel::Status::PAID)
		.setPrice(100);
	std::string json = testData.toJson();
	MockResponse resp;
	std::shared_ptr<PaymentRepository> rep = std::make_shared<MockPaymentRepository>();
	Payment::CreateController controller(rep);
	MockRequest req(json);
	static_cast<MockPaymentRepository *>(rep.get())->setUid("f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);
	assert(resp.get("location") == "/payment?payment_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");
	return 0;
}
