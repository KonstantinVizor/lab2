#ifndef __PAYMENTCREATECONTROLLER_H__
#define __PAYMENTCREATECONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/PaymentRepository.h"

namespace Payment
{
class CreateController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		CreateController() = default;
		explicit CreateController(const CreateController &) = delete;
		CreateController(CreateController &&) = delete;
		~CreateController() = default;
	
		CreateController(const std::shared_ptr<PaymentRepository> paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
