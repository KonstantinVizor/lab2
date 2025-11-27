#include "../../inc/models/ReservationModel.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <ctime>
#include <iomanip>
#include <sstream>

ReservationModel::ReservationModel(const ReservationModel &obj) :
						_id(obj._id),
						_reservationUid(obj._reservationUid),
						_username(obj._username),
						_paymentUid(obj._paymentUid),
						_hotelId(obj._hotelId),
						_status(obj._status),
						_startDate(obj._startDate),
						_endDate(obj._endDate)
{}

ReservationModel::ReservationModel(ReservationModel &&obj) :
						_id(obj._id),
						_reservationUid(obj._reservationUid),
						_username(obj._username),
						_paymentUid(obj._paymentUid),
						_hotelId(obj._hotelId),
						_status(obj._status),
						_startDate(obj._startDate),
						_endDate(obj._endDate)
{}

const uint32_t& ReservationModel::getId() const
{
	return _id;
}

const std::string& ReservationModel::getReservationUid() const
{
	return _reservationUid;
}

const std::string& ReservationModel::getUsername() const
{
	return _username;
}

const std::string& ReservationModel::getPaymentUid() const
{
	return _paymentUid;
}

const uint32_t& ReservationModel::getHotelId() const
{
	return _hotelId;
}

const std::string& ReservationModel::getStatus() const
{
	return _status;
}

const std::time_t& ReservationModel::getStartDate() const
{
	return _startDate;
}

const std::time_t& ReservationModel::getEndDate() const
{
	return _endDate;
}

ReservationModel& ReservationModel::setId(uint32_t id)
{
	_id = id;
	return *this;
}

ReservationModel& ReservationModel::setReservationUid(const std::string &uid)
{
	_reservationUid = uid;
	return *this;
}

ReservationModel& ReservationModel::setUsername(const std::string &username)
{
	_username = username;
	return *this;
}

ReservationModel& ReservationModel::setPaymentUid(const std::string &paymentUid)
{
	_paymentUid = paymentUid;
	return *this;
}

ReservationModel& ReservationModel::setHotelId(uint32_t hotelId)
{
	_hotelId = hotelId;
	return *this;
}

ReservationModel& ReservationModel::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

ReservationModel& ReservationModel::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

ReservationModel& ReservationModel::setStartDate(const std::time_t &startDate)
{
	_startDate = startDate;
	return *this;
}

ReservationModel& ReservationModel::setEndDate(const std::time_t &endDate)
{
	_endDate = endDate;
	return *this;
}


bool ReservationModel::fromJson(const std::string &json, bool all)
{
	const char *format = "%Y-%m-%d";
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
	var = data->get("reservationUid");
	if (!var.isEmpty())
		_reservationUid = var.toString();
	else if (all)
		return false;
	var = data->get("username");
	if (!var.isEmpty())
		_username = var.toString();
	else if (all)
		return false;
	var = data->get("paymentUid");
	if (!var.isEmpty())
		_paymentUid = var.toString();
	else if (all)
		return false;
	var = data->get("hotelId");
	if (!var.isEmpty())
		try
		{
			_hotelId = std::stoi(var.toString());
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
	var = data->get("startDate");
	if (!var.isEmpty())
		try
		{
			std::istringstream stream(var.toString());
			std::tm tm;
			std::memset(&tm, 0, sizeof(tm));
			stream >> std::get_time(&tm, format);
			_startDate = std::mktime(&tm);
		}
		catch (...)
		{
			return false;
		}
	else if (all)
		return false;
	var = data->get("endDate");
	if (!var.isEmpty())
		try
		{
			std::istringstream stream(var.toString());
			std::tm tm;
			std::memset(&tm, 0, sizeof(tm));
			stream >> std::get_time(&tm, format);
			_endDate = std::mktime(&tm);
		}
		catch (...)
		{
			return false;
		}
	else if (all)
		return false;
	return true;
}

std::string ReservationModel::toJson() const
{
	const int n = 12;
	char buf1[n];
	char buf2[n];
	const char *format = "%Y-%m-%d";
	std::ostringstream stream;
	Poco::JSON::Object data;
	data.set("id", _id);
	data.set("reservationUid", _reservationUid);
	data.set("username", _username);
	data.set("paymentUid", _paymentUid);
	data.set("hotelId", _hotelId);
	data.set("status", _status);
	std::strftime(buf1, n, format, std::localtime(&_startDate));
	data.set("startDate", buf1);
	std::strftime(buf2, n, format, std::localtime(&_endDate));
	data.set("endDate", buf2);
	data.stringify(stream);
	return stream.str();
}

const ReservationModel& ReservationModel::operator =(const ReservationModel &obj)
{
	_id = obj._id;
	_reservationUid = obj._reservationUid;
	_username = obj._username;
	_paymentUid = obj._paymentUid;
	_hotelId = obj._hotelId;
	_status = obj._status;
	_startDate = obj._startDate;
	_endDate = obj._endDate;
	return *this;
}

bool ReservationModel::operator ==(const ReservationModel &model) const
{
	return _id == model._id &&
		_reservationUid == model._reservationUid &&
		_username == model._username &&
		_paymentUid == model._paymentUid &&
		_hotelId == model._hotelId &&
		_status == model._status &&
		_startDate == model._startDate &&
		_endDate == model._endDate;
}
