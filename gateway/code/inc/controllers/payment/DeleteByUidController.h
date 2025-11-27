#ifndef __PAYMENTDELETEBYUIDCONTROLLER_H__
#define __PAYMENTDELETEBYUIDCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../../inc/repositories/PaymentRepository.h"

namespace Payment
{
class DeleteByUidController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		DeleteByUidController() = default;
		explicit DeleteByUidController(const DeleteByUidController &) = delete;
		DeleteByUidController(DeleteByUidController &&) = delete;
		~DeleteByUidController() = default;
	
		DeleteByUidController(const std::shared_ptr<PaymentRepository> paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
