#include "../../inc/models/ReservationWithHotel.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <iomanip>

ReservationWithHotel::ReservationWithHotel(const ReservationWithHotel &obj) :
							_reservationUid(obj._reservationUid),
							_hotel(obj._hotel),
							_startDate(obj._startDate),
							_endDate(obj._endDate),
							_status(obj._status),
							_paymentUid(obj._paymentUid)
{}

ReservationWithHotel::ReservationWithHotel(ReservationWithHotel &&obj) :
							_reservationUid(obj._reservationUid),
							_hotel(obj._hotel),
							_startDate(obj._startDate),
							_endDate(obj._endDate),
							_status(obj._status),
							_paymentUid(obj._paymentUid)
{}

ReservationWithHotel::ReservationWithHotel(const ReservationModel &obj) :
							_reservationUid(obj.getReservationUid()),
							_startDate(obj.getStartDate()),
							_endDate(obj.getEndDate()),
							_status(obj.getStatus()),
							_paymentUid(obj.getPaymentUid())
{}

const std::string& ReservationWithHotel::getReservationUid() const
{
	return _reservationUid;
}

const HotelInfo& ReservationWithHotel::getHotel() const
{
	return _hotel;
}

const std::time_t& ReservationWithHotel::getStartDate() const
{
	return _startDate;
}

const std::time_t& ReservationWithHotel::getEndDate() const
{
	return _endDate;
}

const std::string& ReservationWithHotel::getStatus() const
{
	return _status;
}

const std::string& ReservationWithHotel::getPaymentUid() const
{
	return _paymentUid;
}

ReservationWithHotel& ReservationWithHotel::setReservationUid(const std::string &reservationUid)
{
	_reservationUid = reservationUid;
	return *this;
}

ReservationWithHotel& ReservationWithHotel::setHotelInfo(const HotelInfo &hotel)
{
	_hotel = hotel;
	return *this;
}

ReservationWithHotel& ReservationWithHotel::setStartDate(const std::time_t &startDate)
{
	_startDate = startDate;
	return *this;
}

ReservationWithHotel& ReservationWithHotel::setEndDate(const std::time_t &endDate)
{
	_endDate = endDate;
	return *this;
}

ReservationWithHotel& ReservationWithHotel::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

ReservationWithHotel& ReservationWithHotel::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

ReservationWithHotel& ReservationWithHotel::setPaymentUid(const std::string &paymentUid)
{
	_paymentUid = paymentUid;
	return *this;
}

bool ReservationWithHotel::fromJson(const std::string &json, bool all)
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

std::string ReservationWithHotel::toJson() const
{
	const int n = 12;
	char buf1[n];
	char buf2[n];
	const char *format = "%Y-%m-%d";
	std::ostringstream stream;
	Poco::JSON::Object data;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr ptr;
	ptr = parser.parse(_hotel.toJson()).extract<Poco::JSON::Object::Ptr>();
	data.set("reservationUid", _reservationUid);
	data.set("hotel", ptr);
	std::strftime(buf1, n, format, std::localtime(&_startDate));
	data.set("startDate", buf1);
	std::strftime(buf2, n, format, std::localtime(&_endDate));
	data.set("endDate", buf2);
	data.set("status", _status);
	data.set("paymentUid", _paymentUid);
	data.stringify(stream);
	return stream.str();
}

const ReservationWithHotel& ReservationWithHotel::operator =(const ReservationWithHotel &obj)
{
	_reservationUid = obj._reservationUid;
	_hotel = obj._hotel;
	_startDate = obj._startDate;
	_endDate = obj._endDate;
	_status = obj._status;
	_paymentUid = obj._paymentUid;
	return *this;
}
