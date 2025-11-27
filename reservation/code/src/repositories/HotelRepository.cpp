#include "../../inc/repositories/HotelRepository.h"
#include "Poco/Data/Statement.h"
#include "Poco/UUID.h"
#include <Poco/Data/Binding.h>
#include <Poco/Data/Extraction.h>
#include <Poco/Data/Position.h>
#include <Poco/UUIDGenerator.h>
#include <vector>

HotelRepository& HotelRepository::setSession(const SessionPtr &session)
{
	_session = session;
	return *this;
}

std::optional<HotelResponce> HotelRepository::getByUid(const std::string &uid) const
{
	std::string muid = uid;
	std::vector<HotelModelTuple> tuple;
	HotelResponce result;
	std::string request = "SELECT id, hotel_uid, name, country, \
			       city, address, stars, price \
				FROM hotels WHERE hotel_uid = $1";
	*_session << request, 
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	if (tuple.size() == 0)
		return {};
	result.setId(tuple[0].get<0>())
		.setHotelUid(tuple[0].get<1>())
		.setName(tuple[0].get<2>())
		.setCountry(tuple[0].get<3>())
		.setCity(tuple[0].get<4>())
		.setAddress(tuple[0].get<5>())
		.setStars(tuple[0].get<6>())
		.setPrice(tuple[0].get<7>());
	return result;
}

std::optional<HotelResponce> HotelRepository::getById(int32_t id) const
{
	std::vector<HotelModelTuple> tuple;
	HotelResponce result;
	std::string request = "SELECT id, hotel_uid, name, country, \
			       city, address, stars, price \
				FROM hotels WHERE id = $1";
	*_session << request, 
			Poco::Data::Keywords::use(id),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	if (tuple.size() == 0)
		return {};
	result.setId(tuple[0].get<0>())
		.setHotelUid(tuple[0].get<1>())
		.setName(tuple[0].get<2>())
		.setCountry(tuple[0].get<3>())
		.setCity(tuple[0].get<4>())
		.setAddress(tuple[0].get<5>())
		.setStars(tuple[0].get<6>())
		.setPrice(tuple[0].get<7>());
	return result;
}

std::vector<HotelResponce> HotelRepository::getAll(uint32_t pageNumber, uint32_t pageSize) const
{
	uint32_t offset = (pageNumber - 1) * pageSize;
	std::vector<HotelModelTuple> tuple;
	std::vector<HotelResponce> result;
	std::string request = "SELECT id, hotel_uid, name, country, \
			       city, address, stars, price \
				FROM hotels OFFSET $1 LIMIT $2";
	*_session << request, 
			Poco::Data::Keywords::use(offset),
			Poco::Data::Keywords::use(pageSize),
			Poco::Data::Keywords::into(tuple),
			Poco::Data::Keywords::now;
	for (int i = 0; i < static_cast<int>(tuple.size()); i++)
		result.push_back(HotelResponce().setId(tuple[0].get<0>())
						.setHotelUid(tuple[0].get<1>())
						.setName(tuple[0].get<2>())
						.setCountry(tuple[0].get<3>())
						.setCity(tuple[0].get<4>())
						.setAddress(tuple[0].get<5>())
						.setStars(tuple[0].get<6>())
						.setPrice(tuple[0].get<7>()));
	return result;
}

std::pair<uint32_t, std::string> HotelRepository::create(const HotelResponce &model) const
{
	uint32_t id;
	Poco::UUIDGenerator generator;
	std::string request = "INSERT INTO hotel(hotel_uid, name, country, city, \
			       		address, stars, price) \
					VALUES ($1, $2, $3, $4, $5, $6, $7) RETURNING id";
	HotelModelNoIdTuple tuple = {
		generator.createV7().toString(),
		model.getName(),
		model.getCountry(),
		model.getCity(),
		model.getAddress(),
		model.getStars(),
		model.getPrice()};
	*_session << request,
			Poco::Data::Keywords::use(tuple),
			Poco::Data::Keywords::into(id),
			Poco::Data::Keywords::now;
	return {id, tuple.get<0>()};
}

const HotelRepository& HotelRepository::deleteByUid(const std::string &uid) const
{
	std::string muid = uid;
	std::string request = "DELETE FROM hotels WHERE hotel_uid = $1";
	*_session << request,
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::now;
	return *this;
}

const HotelRepository& HotelRepository::updateByUid(const std::string &uid, const HotelResponce &model) const
{
	std::string muid = uid;
	std::string nuid = model.getHotelUid();
	std::string name = model.getName();
	std::string country = model.getCountry();
	std::string city = model.getCity();
	std::string address = model.getAddress();
	uint32_t stars = model.getStars();
	uint32_t price = model.getPrice();
	std::string request = "UPDATE hotel SET hotel_uid = $1, \
			       			name = $2, \
						country = $3, \
						city = $4, \
						address = $5, \
						stars = $6, \
						price = $7 \
					WHERE hotel_uid = $8";
	*_session << request,
			Poco::Data::Keywords::use(nuid),
			Poco::Data::Keywords::use(name),
			Poco::Data::Keywords::use(country),
			Poco::Data::Keywords::use(city),
			Poco::Data::Keywords::use(address),
			Poco::Data::Keywords::use(stars),
			Poco::Data::Keywords::use(price),
			Poco::Data::Keywords::use(muid),
			Poco::Data::Keywords::now;
	return *this;	
}
