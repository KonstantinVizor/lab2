#ifndef __PAYMENTGETBYUIDCONTROLLER_H__
#define __PAYMENTGETBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/PaymentRepository.h"

namespace Payment
{
class GetByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		GetByUidController() = default;
		explicit GetByUidController(const GetByUidController &) = delete;
		GetByUidController(GetByUidController &&) = delete;
		~GetByUidController() = default;
	
		GetByUidController(const std::shared_ptr<PaymentRepository> paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
