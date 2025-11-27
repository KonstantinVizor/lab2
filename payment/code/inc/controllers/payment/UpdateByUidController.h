#ifndef __PAYMENTUPDATEBYUIDCONTROLLER_H__
#define __PAYMENTUPDATEBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/PaymentRepository.h"

namespace Payment
{
class UpdateByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		UpdateByUidController() = default;
		explicit UpdateByUidController(const UpdateByUidController &) = delete;
		UpdateByUidController(UpdateByUidController &&) = delete;
		~UpdateByUidController() = default;
	
		UpdateByUidController(const std::shared_ptr<PaymentRepository> paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
