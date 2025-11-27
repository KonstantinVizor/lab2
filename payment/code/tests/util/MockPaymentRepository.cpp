#include "MockPaymentRepository.h"
#include <optional>

void MockPaymentRepository::setTestData(const std::vector<PaymentModel> &data)
{
	_data = data;
}

void MockPaymentRepository::setTestData(const PaymentModel &data)
{
	_singleData = data;
}

void MockPaymentRepository::setId(uint32_t id)
{
	_id = id;
}

void MockPaymentRepository::setUid(const std::string &uid)
{
	_uid = uid;
}

std::vector<PaymentModel> MockPaymentRepository::getAll() const
{
	return _data;
}	

std::optional<PaymentModel> MockPaymentRepository::getByUid(const std::string &uid) const
{
	if (uid == _singleData.getPaymentUid())
		return std::optional(_singleData);
	return {};
}

const PaymentRepository& MockPaymentRepository::deleteByUid([[maybe_unused]] const std::string &uid) const
{
	return *this;
}

std::pair<uint32_t, std::string> MockPaymentRepository::create([[maybe_unused]] const PaymentModel &model) const
{
	return {_id, _uid};
}

const PaymentRepository& MockPaymentRepository::updateByUid(const std::string &uid, [[maybe_unused]] const PaymentModel &model) const
{
	if (uid == _singleData.getPaymentUid())
		const_cast<PaymentModel &>(_singleData) = model;
	return *this;
}
