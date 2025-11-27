#include "../../inc/models/LoyaltyModel.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

LoyaltyModel::LoyaltyModel(const LoyaltyModel &obj) :
				_id(obj._id),
				_username(obj._username),
				_reservationCount(obj._reservationCount),
				_status(obj._status),
				_discont(obj._discont)
{}

LoyaltyModel::LoyaltyModel(LoyaltyModel &&obj) :
				_id(obj._id),
				_username(obj._username),
				_reservationCount(obj._reservationCount),
				_status(obj._status),
				_discont(obj._discont)
{}

const uint32_t& LoyaltyModel::getId() const
{
	return _id;
}

const std::string& LoyaltyModel::getUsername() const
{
	return _username;
}

const uint32_t& LoyaltyModel::getReservationCount() const
{
	return _reservationCount;
}

const std::string& LoyaltyModel::getStatus() const
{
	return _status;
}

const uint32_t& LoyaltyModel::getDiscont() const
{
	return _discont;
}

LoyaltyModel& LoyaltyModel::setId(uint32_t id)
{
	_id = id;
	return *this;
}

LoyaltyModel& LoyaltyModel::setUsername(const std::string &username)
{
	_username = username;
	return *this;
}

LoyaltyModel& LoyaltyModel::setReservationCount(uint32_t reservationCount)
{
	_reservationCount = reservationCount;
	return *this;
}

LoyaltyModel& LoyaltyModel::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

LoyaltyModel& LoyaltyModel::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

LoyaltyModel& LoyaltyModel::setDiscont(uint32_t discont)
{
	_discont = discont;
	return *this;
}

bool LoyaltyModel::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
	}
	catch (...)
	{
		return false;
	}
	var = data->get("id");
	if (!var.isEmpty())
		try
		{
			_id = std::stoi(var.toString());
		}
		catch (...)
		{
			return false;
		}
	var = data->get("username");
	if (!var.isEmpty())
		_username = var.toString();
	else if (all)
		return false;
	var = data->get("reservationCount");
	if (!var.isEmpty())
		try
		{
			_reservationCount = std::stoi(var.toString());
		}
		catch (...)
		{
			return false;
		}
	else if (all)
		return false;
	var = data->get("status");
	if (!var.isEmpty())
		_status = var.toString();
	else if (all)
		return false;
	var = data->get("discount");
	if (!var.isEmpty())
		try
		{
			_discont = std::stoi(var.toString());
		}
		catch (...)
		{
			return false;
		}
	else if (all)
		return false;
	return true;
}

std::string LoyaltyModel::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("id", _id);
	data.set("username", _username);
	data.set("reservationCount", _reservationCount);
	data.set("status", _status);
	data.set("discount", _discont);
	data.stringify(stream);
	return stream.str();
}

const LoyaltyModel& LoyaltyModel::operator =(const LoyaltyModel &obj)
{
	_id = obj._id;
	_username = obj._username;
	_reservationCount = obj._reservationCount;
	_status = obj._status;
	_discont = obj._discont;
	return *this;
}

bool LoyaltyModel::operator ==(const LoyaltyModel &model) const
{
	return _id == model._id &&
		_reservationCount == model._reservationCount &&
		_username == model._username &&
		_status == model._status &&
		_discont == model._discont;
}
