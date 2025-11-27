#include <cassert>
#include "../../inc/controllers/loyalty/DeleteByUsernameController.h"
#include "../util/MockResponse.h"
#include "../util/MockRequest.h"
#include "../util/MockLoyaltyRepository.h"

int main(void)
{
	std::shared_ptr<LoyaltyRepository> rep = std::make_shared<MockLoyaltyRepository>();
	MockResponse resp;
	MockRequest req;
	Loyalty::DeleteByUsernameController controller(rep);
	req.setURI("/loyalty?username=Kostya");

	controller.handleRequest(req, resp);
	
	assert(resp.getStatus() == Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
	return 0;
}
