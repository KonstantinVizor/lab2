#include "../../inc/models/HotelInfo.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <string>

HotelInfo::HotelInfo(const HotelInfo &obj) :
				_hotelUid(obj._hotelUid),
				_name(obj._name),
				_fullAddress(obj._fullAddress),
				_stars(obj._stars)
{}

HotelInfo::HotelInfo(HotelInfo &&obj) :
				_hotelUid(obj._hotelUid),
				_name(obj._name),
				_fullAddress(obj._fullAddress),
				_stars(obj._stars)
{}

HotelInfo::HotelInfo(const HotelResponce &resp) :
				_hotelUid(resp.getHotelUid()),
				_name(resp.getName()),
				_fullAddress(resp.getCountry() + ", " +
						resp.getCity() + ", " +
						resp.getAddress()),
				_stars(resp.getStars())
{}

const std::string& HotelInfo::getHotelUid() const
{
	return _hotelUid;
}

const std::string& HotelInfo::getName() const
{
	return _name;
}

const std::string& HotelInfo::getFullAddress() const
{
	return _fullAddress;
}

const uint32_t& HotelInfo::getStars() const
{
	return _stars;
}

HotelInfo& HotelInfo::setHotelUid(const std::string &hotelUid)
{
	_hotelUid = hotelUid;
	return *this;
}

HotelInfo& HotelInfo::setName(const std::string &name)
{
	_name = name;
	return *this;
}

HotelInfo& HotelInfo::setFullAddress(const std::string &fullAddress)
{
	_fullAddress = fullAddress;
	return *this;
}

HotelInfo& HotelInfo::setStars(const uint32_t &stars)
{
	_stars = stars;
	return *this;
}

bool HotelInfo::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
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
		var = data->get("fullAddress");
		if (!var.isEmpty())
			_fullAddress = var.toString();
		else if (all)
			return false;
		var = data->get("stars");
		if (!var.isEmpty())
			_stars = std::stoi(var.toString());
		else if (all)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string HotelInfo::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("hotelUid", _hotelUid);
	data.set("name", _name);
	data.set("fullAddress", _fullAddress);
	data.set("stars", _stars);
	data.stringify(stream);
	return stream.str();
}

const HotelInfo& HotelInfo::operator =(const HotelInfo &obj)
{
	_hotelUid = obj._hotelUid;
	_name = obj._name;
	_fullAddress = obj._fullAddress;
	_stars = obj._stars;
	return *this;
}
