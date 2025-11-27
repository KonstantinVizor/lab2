#ifndef __PAYMENTREPOSITORY_H__
#define __PAYMENTREPOSITORY_H__

#include <Poco/Data/Session.h>
#include <Poco/Tuple.h>
#include <memory>
#include <optional>
#include "../models/PaymentModel.h"

class PaymentRepository
{
	public:
		using SessionPtr = std::shared_ptr<Poco::Data::Session>;
		using PaymentModelTuple = Poco::Tuple<uint32_t, std::string, std::string, uint32_t>;
		using PaymentModelNoIdTuple = Poco::Tuple<std::string, std::string, uint32_t>;

	protected:
		SessionPtr _session;

	public:
		PaymentRepository() = default;
		explicit PaymentRepository(const PaymentRepository &) = delete;
		PaymentRepository(PaymentRepository &&) = delete;
		~PaymentRepository() = default;
		
		virtual PaymentRepository& setSession(const SessionPtr &session);
	
		virtual std::optional<PaymentModel> getByUid(const std::string &uid) const;
		virtual std::vector<PaymentModel> getAll() const;
		virtual std::pair<uint32_t, std::string> create(const PaymentModel &model) const;
		virtual const PaymentRepository& deleteByUid(const std::string &uid) const;
		virtual const PaymentRepository& updateByUid(const std::string &uid, const PaymentModel &model) const;
};

#endif
