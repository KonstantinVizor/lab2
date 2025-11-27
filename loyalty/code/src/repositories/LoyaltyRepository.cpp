#include "../../inc/repositories/LoyaltyRepository.h"
#include "Poco/Data/Statement.h"
//#include "Poco/UUID.h"
#include <Poco/Data/Binding.h>
#include <Poco/Data/Extraction.h>
#include <Poco/Data/Position.h>
#include <Poco/UUIDGenerator.h>
#include <vector>

LoyaltyRepository& LoyaltyRepository::setSession(const SessionPtr &session)
{
	_session = session;
	return *this;
}

std::optional<LoyaltyModel> LoyaltyRepository::getByUsername(const std::string &username) const
{
	std::string uname = username;
	std::vector<LoyaltyModelTuple> tuple;
	LoyaltyModel result;
	std::string request = "SELECT id, username, reservation_count, status, discount \
				FROM loyalty WHERE username = $1";
	*_session << request, 
			Poco::Data::Keywords::use(uname),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	if (tuple.size() == 0)
		return {};
	result.setId(tuple[0].get<0>())
		.setUsername(tuple[0].get<1>())
		.setReservationCount(tuple[0].get<2>())
		.setStatus(tuple[0].get<3>())
		.setDiscont(tuple[0].get<4>());
	return result;
}

std::vector<LoyaltyModel> LoyaltyRepository::getAll() const
{
	std::vector<LoyaltyModelTuple> tuple;
	std::vector<LoyaltyModel> result;
	std::string request = "SELECT id, username, reservation_count, status, discount \
				FROM loyalty";
	*_session << request, 
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	for (int i = 0; i < static_cast<int>(tuple.size()); i++)
		result.push_back(LoyaltyModel().setId(tuple[0].get<0>())
					.setUsername(tuple[0].get<1>())
					.setReservationCount(tuple[0].get<2>())
					.setStatus(tuple[0].get<3>())
					.setDiscont(tuple[0].get<4>()));
	return result;
}

uint32_t LoyaltyRepository::create(const LoyaltyModel &model) const
{
	uint32_t id;
//	Poco::UUIDGenerator generator;
	std::string request = "INSERT INTO loyalty(username, reservation_count, status, discount) \
					VALUES ($1, $2, $3, $4) RETURNING id";
	LoyaltyModelNoIdTuple tuple = {
//		generator.createV7().toString(),
		model.getUsername(),
		model.getReservationCount(),
		model.getStatus(),
		model.getDiscont()};
	*_session << request,
			Poco::Data::Keywords::use(tuple),
			Poco::Data::Keywords::into(id),
			Poco::Data::Keywords::now;
	return id;
}

const LoyaltyRepository& LoyaltyRepository::deleteByUsername(const std::string &username) const
{
	std::string uname = username;
	std::string request = "DELETE FROM loyalty WHERE username = $1";
	*_session << request,
			Poco::Data::Keywords::use(uname),
			Poco::Data::Keywords::now;
	return *this;
}

const LoyaltyRepository& LoyaltyRepository::updateByUsername(const std::string &username, const LoyaltyModel &model) const
{
	std::string uname = username;
	std::string musername = model.getUsername();
	int reservationCount = model.getReservationCount();
	std::string status = model.getStatus();
	int discont = model.getDiscont();
	std::string request = "UPDATE loyalty SET username = $1, \
						reservation_count = $2, \
						status = $3, \
						discount = $4 \
					WHERE username = $5";
	*_session << request,
			Poco::Data::Keywords::use(musername),
			Poco::Data::Keywords::use(reservationCount),
			Poco::Data::Keywords::use(status),
			Poco::Data::Keywords::use(discont),
			Poco::Data::Keywords::use(uname),
			Poco::Data::Keywords::now;
	return *this;	
}
