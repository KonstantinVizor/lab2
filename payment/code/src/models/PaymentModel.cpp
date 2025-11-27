#include "../../inc/models/PaymentModel.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

PaymentModel::PaymentModel(const PaymentModel &obj) :
				_id(obj._id),
				_paymentUid(obj._paymentUid),
				_status(obj._status),
				_price(obj._price)
{}

PaymentModel::PaymentModel(PaymentModel &&obj) :
				_id(obj._id),
				_paymentUid(obj._paymentUid),
				_status(obj._status),
				_price(obj._price)
{}

const uint32_t& PaymentModel::getId() const
{
	return _id;
}

const std::string& PaymentModel::getPaymentUid() const
{
	return _paymentUid;
}

const std::string& PaymentModel::getStatus() const
{
	return _status;
}

const uint32_t& PaymentModel::getPrice() const
{
	return _price;
}

PaymentModel& PaymentModel::setId(uint32_t id)
{
	_id = id;
	return *this;
}

PaymentModel& PaymentModel::setPaymentUid(const std::string &uuid)
{
	_paymentUid = uuid;
	return *this;
}

PaymentModel& PaymentModel::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

PaymentModel& PaymentModel::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

PaymentModel& PaymentModel::setPrice(uint32_t price)
{
	_price = price;
	return *this;
}

bool PaymentModel::fromJson(const std::string &json, bool all)
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
		std::cout << "Cannot parse\n";
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
			std::cout << "Bad id\n";
			return false;
		}
	var = data->get("paymentUid");
	if (!var.isEmpty())
		_paymentUid = var.toString();
	var = data->get("status");
	if (!var.isEmpty())
		_status = var.toString();
	else if (all)
	{
		std::cout << "Bad status\n";
		return false;
	}
	var = data->get("price");
	if (!var.isEmpty())
		try
		{
			_price = std::stoi(var.toString());
		}
		catch (...)
		{
			return false;
		}
	else if (all)
	{
		return false;
	}
	return true;
}

std::string PaymentModel::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("id", _id);
	data.set("paymentUid", _paymentUid);
	data.set("status", _status);
	data.set("price", _price);
	data.stringify(stream);
	return stream.str();
}

const PaymentModel& PaymentModel::operator =(const PaymentModel &obj)
{
	_id = obj._id;
	_paymentUid = obj._paymentUid;
	_status = obj._status;
	_price = obj._price;
	return *this;
}

bool PaymentModel::operator ==(const PaymentModel &model) const
{
	return _id == model._id &&
		_paymentUid == model._paymentUid &&
		_status == model._status &&
		_price == model._price;
}
