#include <cassert>
#include "../../inc/controllers/payment/UpdateByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPaymentRepository.h"

int main(void)
{
	std::shared_ptr<PaymentRepository> rep = std::make_shared<MockPaymentRepository>();
	PaymentModel testData, resData;
	testData.setId(0)
		.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setStatus(PaymentModel::Status::CANCELED)
		.setPrice(100);
	resData.setId(0)
		.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setStatus(PaymentModel::Status::PAID)
		.setPrice(30);
	std::string updateJson = "{\"status\":\"PAID\",\"price\":30}";
	MockResponse resp;
	Payment::UpdateByUidController controller(rep);
	static_cast<MockPaymentRepository *>(rep.get())->setTestData(testData);
	MockRequest req(updateJson);
	req.setURI("/payment?payment_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	PaymentModel tmp1, tmp2;
	tmp1.fromJson(resp.getStream().str());
	tmp2 = rep->getByUid(resData.getPaymentUid()).value();
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(tmp1 == tmp2);
	assert(tmp1 == resData);
	return 0;
}
