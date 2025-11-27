#ifndef __PAYMENTGETALLCONTROLLER_H__
#define __PAYMENTGETALLCONTROLLER_H__

#include <Poco/Net/HTTPRequestHandler.h>
#include <memory>
#include "../../repositories/PaymentRepository.h"

namespace Payment
{
// not used
class GetAllController : public Poco::Net::HTTPRequestHandler
{
	private:
		std::shared_ptr<PaymentRepository> _paymentRepository;

	public:
		GetAllController() = default;
		explicit GetAllController(const GetAllController &) = delete;
		GetAllController(GetAllController &&) = delete;
		~GetAllController() = default;

		GetAllController(const std::shared_ptr<PaymentRepository> &paymentRepository);

		virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
						Poco::Net::HTTPServerResponse &resp) override;
};
};

#endif
