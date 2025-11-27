#ifndef __MOCKPAYMENTREPOSITORY_H__
#define __MOCKPAYMENTREPOSITORY_H__

#include "../../inc/repositories/PaymentRepository.h"

class MockPaymentRepository : public PaymentRepository
{
	private:
		std::vector<PaymentModel> _data;
		PaymentModel _singleData;
		uint32_t _id;
		std::string _uid;

	public:
		void setTestData(const std::vector<PaymentModel> &data);
		void setTestData(const PaymentModel &data);
		void setId(uint32_t id);
		void setUid(const std::string &uid);
		virtual std::vector<PaymentModel> getAll() const override;
		virtual std::optional<PaymentModel> getByUid(const std::string &uid) const override;
		virtual const PaymentRepository& deleteByUid(const std::string &uid) const override;
		virtual std::pair<uint32_t, std::string> create(const PaymentModel &model) const override;
		virtual const PaymentRepository& updateByUid(const std::string &uid, const PaymentModel &model) const override;
};

#endif
