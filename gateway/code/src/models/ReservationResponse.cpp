#include "../../inc/models/ReservationResponse.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <iomanip>

ReservationResponse::ReservationResponse(const ReservationResponse &obj) :
							_reservationUid(obj._reservationUid),
							_hotel(obj._hotel),
							_startDate(obj._startDate),
							_endDate(obj._endDate),
							_status(obj._status),
							_payment(obj._payment)
{}

ReservationResponse::ReservationResponse(ReservationResponse &&obj) :
							_reservationUid(obj._reservationUid),
							_hotel(obj._hotel),
							_startDate(obj._startDate),
							_endDate(obj._endDate),
							_status(obj._status),
							_payment(obj._payment)
{}

const std::string& ReservationResponse::getReservationUid() const
{
	return _reservationUid;
}

const HotelInfo& ReservationResponse::getHotel() const
{
	return _hotel;
}

const std::time_t& ReservationResponse::getStartDate() const
{
	return _startDate;
}

const std::time_t& ReservationResponse::getEndDate() const
{
	return _endDate;
}

const std::string& ReservationResponse::getStatus() const
{
	return _status;
}

const PaymentInfo& ReservationResponse::getPayment() const
{
	return _payment;
}

ReservationResponse& ReservationResponse::setReservationUid(const std::string &reservationUid)
{
	_reservationUid = reservationUid;
	return *this;
}

ReservationResponse& ReservationResponse::setHotel(const HotelInfo &hotel)
{
	_hotel = hotel;
	return *this;
}

ReservationResponse& ReservationResponse::setStartDate(const std::time_t &startDate)
{
	_startDate = startDate;
	return *this;
}

ReservationResponse& ReservationResponse::setEndDate(const std::time_t &endDate)
{
	_endDate = endDate;
	return *this;
}

ReservationResponse& ReservationResponse::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

ReservationResponse& ReservationResponse::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

ReservationResponse& ReservationResponse::setPayment(const PaymentInfo &payment)
{
	_payment = payment;
	return *this;
}

bool ReservationResponse::fromJson(const std::string &json, bool all)
{
	const char *format = "%Y-%m-%d";
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
		var = data->get("reservationUid");
		if (!var.isEmpty())
			_reservationUid = var.toString();
		else if (all)
			return false;
		var = data->get("hotel");
		if (!var.isEmpty())
			_hotel.fromJson(var.toString());
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
		var = data->get("status");
		if (!var.isEmpty())
			_status = var.toString();
		else if (all)
			return false;
		var = data->get("payment");
		if (!var.isEmpty())
			_payment.fromJson(var.toString());
		else if (all)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

std::string ReservationResponse::toJson() const
{
	const int n = 12;
	char buf1[n];
	char buf2[n];
	const char *format = "%Y-%m-%d";
	std::ostringstream stream;
	Poco::JSON::Object data;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr obj;
	obj = parser.parse(_hotel.toJson()).extract<Poco::JSON::Object::Ptr>();
	data.set("reservationUid", _reservationUid);
	data.set("hotel", obj);
	std::strftime(buf1, n, format, std::localtime(&_startDate));
	data.set("startDate", buf1);
	std::strftime(buf2, n, format, std::localtime(&_endDate));
	data.set("endDate", buf2);
	data.set("status", _status);
	obj = parser.parse(_payment.toJson()).extract<Poco::JSON::Object::Ptr>();
	data.set("payment", obj);
	data.stringify(stream);
	return stream.str();
}

const ReservationResponse& ReservationResponse::operator =(const ReservationResponse &obj)
{
	_reservationUid = obj._reservationUid;
	_hotel = obj._hotel;
	_startDate = obj._startDate;
	_endDate = obj._endDate;
	_status = obj._status;
	_payment = obj._payment;
	return *this;
}
