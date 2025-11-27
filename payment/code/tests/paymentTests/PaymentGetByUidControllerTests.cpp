#include <cassert>
#include "../../inc/controllers/payment/GetByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPaymentRepository.h"
#include <Poco/Net/HTTPResponse.h>

int main(void)
{
	std::shared_ptr<PaymentRepository> rep = std::make_shared<MockPaymentRepository>();
	PaymentModel testData;
	testData.setId(0)
		.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
		.setStatus(PaymentModel::Status::CANCELED)
		.setPrice(100);
	MockResponse resp;
	MockRequest req;
	static_cast<MockPaymentRepository *>(rep.get())->setTestData(testData);
	bool flag;
	Payment::GetByUidController controller(rep);
	req.setURI("/payment?payment_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	PaymentModel tmp;
	std::string json = resp.getStream().str();
	flag = tmp.fromJson(json);
	assert(flag);
	assert(tmp == testData);

	
	req.setURI("/payment?payment_uid=f47ac10b-58cc-4372-a567-0e02b2c3d434");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
	return 0;
}
