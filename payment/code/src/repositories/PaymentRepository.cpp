#include "../../inc/repositories/PaymentRepository.h"
#include "Poco/Data/Statement.h"
#include "Poco/UUID.h"
#include <Poco/Data/Binding.h>
#include <Poco/Data/Extraction.h>
#include <Poco/Data/Position.h>
#include <Poco/UUIDGenerator.h>
#include <vector>

PaymentRepository& PaymentRepository::setSession(const SessionPtr &session)
{
	_session = session;
	return *this;
}

std::optional<PaymentModel> PaymentRepository::getByUid(const std::string &uid) const
{
	std::string muid = uid;
	std::vector<PaymentModelTuple> tuple;
	PaymentModel result;
	std::string request = "SELECT id, payment_uid, status, price \
				FROM payment WHERE payment_uid = $1";
	*_session << request, 
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	if (tuple.size() == 0)
		return {};
	result.setId(tuple[0].get<0>())
		.setPaymentUid(tuple[0].get<1>())
		.setStatus(tuple[0].get<2>())
		.setPrice(tuple[0].get<3>());
	return result;
}

std::vector<PaymentModel> PaymentRepository::getAll() const
{
	std::vector<PaymentModelTuple> tuple;
	std::vector<PaymentModel> result;
	std::string request = "SELECT id, payment_uid, status, price \
				FROM payment";
	*_session << request, 
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	for (int i = 0; i < static_cast<int>(tuple.size()); i++)
		result.push_back(PaymentModel().setId(tuple[0].get<0>())
					.setPaymentUid(tuple[0].get<1>())
					.setStatus(tuple[0].get<2>())
					.setPrice(tuple[0].get<3>()));
	return result;
}

std::pair<uint32_t, std::string> PaymentRepository::create(const PaymentModel &model) const
{
	uint32_t id;
	Poco::UUIDGenerator generator;
	std::string request = "INSERT INTO payment(payment_uid, status, price) \
					VALUES ($1, $2, $3) RETURNING id";
	PaymentModelNoIdTuple tuple = {
		generator.createV7().toString(),
		model.getStatus(),
		model.getPrice()};
	*_session << request,
			Poco::Data::Keywords::use(tuple),
			Poco::Data::Keywords::into(id),
			Poco::Data::Keywords::now;
	return {id, tuple.get<0>()};
}

const PaymentRepository& PaymentRepository::deleteByUid(const std::string &uid) const
{
	std::string muid = uid;
	std::string request = "DELETE FROM payment WHERE payment_uid = $1";
	*_session << request,
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::now;
	return *this;
}

const PaymentRepository& PaymentRepository::updateByUid(const std::string &uid, const PaymentModel &model) const
{
	std::string muid = uid;
	std::string nuid = model.getPaymentUid();
	std::string status = model.getStatus();
	int price = model.getPrice();
	std::string request = "UPDATE payment SET payment_uid = $1, \
						status = $2, \
						price = $3 \
					WHERE payment_uid = $4";
	*_session << request,
			Poco::Data::Keywords::use(nuid),
			Poco::Data::Keywords::use(status),
			Poco::Data::Keywords::use(price),
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::now;
	return *this;	
}
