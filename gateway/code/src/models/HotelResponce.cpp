#include "../../inc/models/HotelResponce.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

HotelResponce::HotelResponce(const HotelResponce &obj) :
				_id(obj._id),
				_hotelUid(obj._hotelUid),
				_name(obj._name),
				_country(obj._country),
				_city(obj._city),
				_address(obj._address),
				_stars(obj._stars),
				_price(obj._price)
{}

HotelResponce::HotelResponce(HotelResponce &&obj) :
				_id(obj._id),
				_hotelUid(obj._hotelUid),
				_name(obj._name),
				_country(obj._country),
				_city(obj._city),
				_address(obj._address),
				_stars(obj._stars),
				_price(obj._price)
{}

const uint32_t& HotelResponce::getId() const
{
	return _id;
}

const std::string& HotelResponce::getHotelUid() const
{
	return _hotelUid;
}

const std::string& HotelResponce::getName() const
{
	return _name;
}

const std::string& HotelResponce::getCountry() const
{
	return _country;
}

const std::string& HotelResponce::getCity() const
{
	return _city;
}
const std::string& HotelResponce::getAddress() const
{
	return _address;
}
const uint32_t& HotelResponce::getStars() const
{
	return _stars;
}
const uint32_t& HotelResponce::getPrice() const
{
	return _price;
}

HotelResponce& HotelResponce::setId(uint32_t id)
{
	_id = id;
	return *this;
}

HotelResponce& HotelResponce::setHotelUid(const std::string &uid)
{
	_hotelUid = uid;
	return *this;
}

HotelResponce& HotelResponce::setName(const std::string &name)
{
	_name = name;
	return *this;
}

HotelResponce& HotelResponce::setCountry(const std::string &country)
{
	_country = country;
	return *this;
}

HotelResponce& HotelResponce::setCity(const std::string &city)
{
	_city = city;
	return *this;
}

HotelResponce& HotelResponce::setAddress(const std::string &address)
{
	_address = address;
	return *this;
}

HotelResponce& HotelResponce::setStars(uint32_t stars)
{
	_stars = stars;
	return *this;
}

HotelResponce& HotelResponce::setPrice(uint32_t price)
{
	_price = price;
	return *this;
}

bool HotelResponce::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
		var = data->get("id");
		if (!var.isEmpty())
			_id = std::stoi(var.toString());
		var = data->get("hotelUid");
		if (!var.isEmpty())
			_hotelUid = var.toString();
		else if (all)
			return false;
		var = data->get("name");
		if (!var.isEmpty())
			_name = var.toString();
		else if (all)
			return false;
		var = data->get("country");
		if (!var.isEmpty())
			_country = var.toString();
		else if (all)
			return false;
		var = data->get("city");
		if (!var.isEmpty())
			_city = var.toString();
		else if (all)
			return false;
		var = data->get("address");
		if (!var.isEmpty())
			_address = var.toString();
		else if (all)
			return false;
		var = data->get("stars");
		if (!var.isEmpty())
			_stars = std::stoi(var.toString());
		else if (all)
			return false;
		var = data->get("price");
		if (!var.isEmpty())
			_price = std::stoi(var.toString());
		else if (all)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string HotelResponce::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("id", _id);
	data.set("hotelUid", _hotelUid);
	data.set("name", _name);
	data.set("country", _country);
	data.set("city", _city);
	data.set("address", _address);
	data.set("stars", _stars);
	data.set("price", _price);
	data.stringify(stream);
	return stream.str();
}

const HotelResponce& HotelResponce::operator =(const HotelResponce &obj)
{
	_id = obj._id;
	_hotelUid = obj._hotelUid;
	_name = obj._name;
	_country = obj._country;
	_city = obj._city;
	_address = obj._address;
	_stars = obj._stars;
	_price = obj._price;
	return *this;
}

bool HotelResponce::operator ==(const HotelResponce &obj) const
{
	return _id == obj._id &&
		_hotelUid == obj._hotelUid &&
		_name == obj._name &&
		_country == obj._country &&
		_city == obj._city &&
		_address == obj._address &&
		_stars == obj._stars &&
		_price == obj._price;
}
