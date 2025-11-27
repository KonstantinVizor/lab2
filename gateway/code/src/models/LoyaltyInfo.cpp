#include "../../inc/models/LoyaltyInfo.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

LoyaltyInfo::LoyaltyInfo(const LoyaltyInfo &obj) :
					_reservationCount(obj._reservationCount),
					_status(obj._status),
					_discont(obj._discont)
{}

LoyaltyInfo::LoyaltyInfo(LoyaltyInfo &&obj) :
				_reservationCount(obj._reservationCount),
				_status(obj._status),
				_discont(obj._discont)
{}

LoyaltyInfo::LoyaltyInfo(const LoyaltyModel &obj) :
				_reservationCount(obj.getReservationCount()),
				_status(obj.getStatus()),
				_discont(obj.getDiscont())
{}
 
const uint32_t& LoyaltyInfo::getReservationCount() const
{
	return _reservationCount;
}

const std::string& LoyaltyInfo::getStatus() const
{
	return _status;
}

const uint32_t& LoyaltyInfo::getDiscount() const
{
	return _discont;
}

LoyaltyInfo& LoyaltyInfo::setReservationCount(uint32_t reservationCount)
{
	_reservationCount = reservationCount;
	return *this;
}

LoyaltyInfo& LoyaltyInfo::setstatus(const std::string &status)
{
	_status = status;
	return *this;
}

LoyaltyInfo& LoyaltyInfo::setstatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

LoyaltyInfo& LoyaltyInfo::setDiscount(uint32_t discount)
{
	_discont = discount;
	return *this;
}

bool LoyaltyInfo::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
		var = data->get("reservationCount");
		if (!var.isEmpty())
			_reservationCount = std::stoi(var.toString());
		else if (all)
			return false;
		var = data->get("status");
		if (!var.isEmpty())
			_status = var.toString();
		else if (all)
			return false;
		var = data->get("discount");
		if (!var.isEmpty())
			_discont = std::stoi(var.toString());
		else if (all)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string LoyaltyInfo::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("reservationCount", _reservationCount);
	data.set("status", _status);
	data.set("discount", _discont);
	data.stringify(stream);
	return stream.str();
}

const LoyaltyInfo& LoyaltyInfo::operator =(const LoyaltyInfo &obj)
{
	_reservationCount = obj._reservationCount;
	_status = obj._status;
	_discont = obj._discont;
	return *this;
}
