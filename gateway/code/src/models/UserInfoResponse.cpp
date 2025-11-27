#include "../../inc/models/UserInfoResponse.h"
#include "Poco/JSON/Array.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

UserInfoResponse::UserInfoResponse(const UserInfoResponse &obj) :
						_reservations(obj._reservations),
						_loyalty(obj._loyalty)
{}

UserInfoResponse::UserInfoResponse(UserInfoResponse &&obj) :
						_reservations(obj._reservations),
						_loyalty(obj._loyalty)
{}

const std::vector<ReservationResponse>& UserInfoResponse::getReservations() const
{
	return _reservations;
}

const LoyaltyInfo& UserInfoResponse::getLoyalty() const
{
	return _loyalty;
}

UserInfoResponse& UserInfoResponse::setReservations(const std::vector<ReservationResponse> &reservations)
{
	_reservations = reservations;
	return *this;
}

UserInfoResponse& UserInfoResponse::setLoyalty(const LoyaltyInfo &loyalty)
{
	_loyalty = loyalty;
	return *this;
}

bool UserInfoResponse::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
		var = data->get("reservations");
		Poco::JSON::Array::Ptr arr = var.extract<Poco::JSON::Array::Ptr>();
		for (uint32_t i = 0; i < arr->size(); i++)
		{
			ReservationResponse tmp;
			if (!tmp.fromJson(arr->get(i).toString()))
				return false;
			_reservations[i] = tmp;
		}
		var = data->get("loyalty");
		if (!var.isEmpty())
			_loyalty.fromJson(var.toString());
		else if (all)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return {};
}

std::string UserInfoResponse::toJson() const
{
	std::ostringstream stream;
	std::string buf = "[";
	Poco::JSON::Object data;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr obj1;
	Poco::JSON::Array::Ptr arr1;
	obj1 = parser.parse(_loyalty.toJson()).extract<Poco::JSON::Object::Ptr>();
	for (uint32_t i = 0; i < _reservations.size(); i++)
	{
		buf += _reservations[i].toJson();
		if (i != (_reservations.size() - 1))
			buf += ",";
	}
	buf += "]";
	data.set("loyalty", obj1);
	arr1 = parser.parse(buf).extract<Poco::JSON::Array::Ptr>();
	data.set("reservations", arr1);
	data.stringify(stream);
	return stream.str();
}

const UserInfoResponse& UserInfoResponse::operator =(const UserInfoResponse &obj)
{
	_reservations = obj._reservations;
	_loyalty = obj._loyalty;
	return *this;
}
