#include <cassert>
#include "../../inc/controllers/payment/GetAllController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPaymentRepository.h"
#include "../util/JsonToVectorConverter.h"

int main(void)
{
	std::shared_ptr<PaymentRepository> rep = std::make_shared<MockPaymentRepository>();
	std::vector<PaymentModel> testData;
	testData.push_back(PaymentModel().setId(0)
					.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d479")
					.setStatus(PaymentModel::Status::CANCELED)
					.setPrice(100));
	testData.push_back(PaymentModel().setId(1)
					.setPaymentUid("f47ac10b-58cc-4372-a567-0e02b2c3d478")
					.setStatus(PaymentModel::Status::PAID)
					.setPrice(200));
	JsonVectorConverter converter;
	MockResponse resp;
	MockRequest req;
	static_cast<MockPaymentRepository *>(rep.get())->setTestData(testData);
	Payment::GetAllController controller(rep);

	controller.handleRequest(req, resp);
	
	std::string json = resp.getStream().str();
	std::vector<std::string> jsons = converter.jsonToVector(json);
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	assert(jsons.size() == testData.size());
	for (int i = 0; i < static_cast<int>(jsons.size()); i++)
	{
		PaymentModel tmp;
		tmp.fromJson(jsons[i]);
		assert(tmp == testData[i]);
	}
	return 0;
}
