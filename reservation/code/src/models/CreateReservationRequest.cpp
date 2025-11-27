#include "../../inc/models/CreateReservationRequest.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <iomanip>

CreateReservationRequest:: CreateReservationRequest(const CreateReservationRequest &obj) :
									_hotelUid(obj._hotelUid),
									_startDate(obj._startDate),
									_endDate(obj._endDate),
									_paymentUid(obj._paymentUid)
{}

CreateReservationRequest::CreateReservationRequest(CreateReservationRequest &&obj) :
									_hotelUid(obj._hotelUid),
									_startDate(obj._startDate),
									_endDate(obj._endDate),
									_paymentUid(obj._paymentUid)
{}

const std::string& CreateReservationRequest::getHotelUid() const
{
	return _hotelUid;
}

const std::time_t& CreateReservationRequest::getStartDate() const
{
	return _startDate;
}

const std::time_t& CreateReservationRequest::getEndDate() const
{
	return _endDate;
}

const std::string& CreateReservationRequest::getPaymentUid() const
{
	return _paymentUid;
}

CreateReservationRequest& CreateReservationRequest::setHoteUid(const std::string &hotelUid)
{
	_hotelUid = hotelUid;
	return *this;
}

CreateReservationRequest& CreateReservationRequest::setStartDate(const std::time_t &startDate)
{
	_startDate = startDate;
	return *this;
}

CreateReservationRequest& CreateReservationRequest::setEndDate(const std::time_t &endDate)
{
	_endDate = endDate;
	return *this;
}

CreateReservationRequest& CreateReservationRequest::setPaymentUid(const std::string &paymentUid)
{
	_paymentUid = paymentUid;
	return *this;
}

bool CreateReservationRequest::fromJson(const std::string &json, bool all)
{
	const char *format = "%Y-%m-%d";
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
		var = data->get("startDate");
		if (!var.isEmpty())
		{
			std::istringstream stream(var.toString());
			std::tm tm;
			std::memset(&tm, 0, sizeof(tm));
			stream >> std::get_time(&tm, format);
			_startDate = std::mktime(&tm);
		}
		else if (all)
			return false;
		var = data->get("endDate");
		if (!var.isEmpty())
		{
			std::istringstream stream(var.toString());
			std::tm tm;
			std::memset(&tm, 0, sizeof(tm));
			stream >> std::get_time(&tm, format);
			_endDate = std::mktime(&tm);
		}
		else if (all)
			return false;
		var = data->get("paymentUid");
		if (!var.isEmpty())
			_paymentUid = var.toString();
		else if (all)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string CreateReservationRequest::toJson() const
{
	const int n = 12;
	char buf1[n];
	char buf2[n];
	const char *format = "%Y-%m-%d";
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("hotelUid", _hotelUid);
	std::strftime(buf1, n, format, std::localtime(&_startDate));
	data.set("startDate", buf1);
	std::strftime(buf2, n, format, std::localtime(&_endDate));
	data.set("endDate", buf2);
	data.set("paymentUid", _paymentUid);
	data.stringify(stream);
	return stream.str();
}

const CreateReservationRequest& CreateReservationRequest::operator =(const CreateReservationRequest &obj)
{
	_hotelUid = obj._hotelUid;
	_startDate = obj._startDate;
	_endDate = obj._endDate;
	_paymentUid = obj._paymentUid;
	return *this;
}
