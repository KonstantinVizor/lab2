#include "../../inc/models/PaymentInfo.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

PaymentInfo::PaymentInfo(const PaymentInfo &obj) :
					_status(obj._status),
					_price(obj._price)
{}

PaymentInfo::PaymentInfo(PaymentInfo &&obj) :
				_status(obj._status),
				_price(obj._price)
{}

const std::string& PaymentInfo::getStatus() const
{
	return _status;
}

const uint32_t& PaymentInfo::getPrice() const
{
	return _price;
}

PaymentInfo& PaymentInfo::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

PaymentInfo& PaymentInfo::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

PaymentInfo& PaymentInfo::setPrice(const uint32_t &price)
{
	_price = price;
	return *this;
}

bool PaymentInfo::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
		var = data->get("status");
		if (!var.isEmpty())
			_status = var.toString();
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

std::string PaymentInfo::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("status", _status);
	data.set("price", _price);
	data.stringify(stream);
	return stream.str();
}

const PaymentInfo& PaymentInfo::operator =(const PaymentInfo &obj)
{
	_status = obj._status;
	_price = obj._price;
	return *this;
}
