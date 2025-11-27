#include <cassert>
#include "../../inc/controllers/payment/DeleteByUidController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockPaymentRepository.h"

int main(void)
{
	std::shared_ptr<PaymentRepository> rep = std::make_shared<MockPaymentRepository>();
	MockResponse resp;
	MockRequest req;
	Payment::DeleteByUidController controller(rep);
	req.setURI("/payment?payment_uid=f47ac10b-58cc-4372-a567-0e02b2c3d479");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	return 0;
}
