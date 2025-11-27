#include "../../inc/models/CreateReservationResponse.h"
#include "Poco/JSONString.h"
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <iomanip>

CreateReservationResponse::CreateReservationResponse(const CreateReservationResponse &obj) :
										_reservationUid(obj._reservationUid),
										_hotelUid(obj._hotelUid),
										_startDate(obj._startDate),
										_endDate(obj._endDate),
										_discount(obj._discount),
										_status(obj._status),
										_payment(obj._payment)
{}

CreateReservationResponse::CreateReservationResponse(CreateReservationResponse &&obj) :
									_reservationUid(obj._reservationUid),
									_hotelUid(obj._hotelUid),
									_startDate(obj._startDate),
									_endDate(obj._endDate),
									_discount(obj._discount),
									_status(obj._status),
									_payment(obj._payment)
{}

CreateReservationResponse::CreateReservationResponse(ReservationModel &obj) :
								_reservationUid(obj.getReservationUid()),
								_startDate(obj.getStartDate()),
								_endDate(obj.getEndDate())
{}

const std::string& CreateReservationResponse::getReservationUid() const
{
	return _reservationUid;
}

const std::string& CreateReservationResponse::getHotelUid() const
{
	return _hotelUid;
}

const std::time_t& CreateReservationResponse::getStartDate() const
{
	return _startDate;
}

const std::time_t& CreateReservationResponse::getEndDate() const
{
	return _endDate;
}

const uint32_t& CreateReservationResponse::getDiscount() const
{
	return _discount;
}

const std::string& CreateReservationResponse::getStatus() const
{
	return _status;
}

const PaymentInfo& CreateReservationResponse::getPayment() const
{
	return _payment;
}

CreateReservationResponse& CreateReservationResponse::setReservationUid(const std::string &reservationUid)
{
	_reservationUid = reservationUid;
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setHotelUid(const std::string &hotelUid)
{
	_hotelUid = hotelUid;
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setStartDate(const std::time_t &startDate)
{
	_startDate = startDate;
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setEndDate(const std::time_t &endDate)
{
	_endDate = endDate;
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setDiscount(const uint32_t &discount)
{
	_discount = discount;
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setStatus(const std::string &status)
{
	_status = status;
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setStatus(const Status &status)
{
	_status = _statuses[status];
	return *this;
}

CreateReservationResponse& CreateReservationResponse::setPayment(const PaymentInfo &payment)
{
	_payment = payment;
	return *this;
}

bool CreateReservationResponse::fromJson(const std::string &json, bool all)
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
		var = data->get("status");
		if (!var.isEmpty())
			_status = var.toString();
		else if (all)
			return false;
		var = data->get("discount");
		if (!var.isEmpty())
			_discount = std::stoi(var.toString());
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

std::string CreateReservationResponse::toJson() const
{
	const int n = 12;
	char buf1[n];
	char buf2[n];
	const char *format = "%Y-%m-%d";
	std::ostringstream stream;
	Poco::JSON::Object data;
	Poco::JSON::Parser parser;
	data.set("reservationUid", _reservationUid);
	data.set("hotelUid", _hotelUid);
	std::strftime(buf1, n, format, std::localtime(&_startDate));
	data.set("startDate", buf1);
	std::strftime(buf2, n, format, std::localtime(&_endDate));
	data.set("endDate", buf2);
	data.set("status", _status);
	data.set("discount", _discount);
	data.set("payment", parser.parse(_payment.toJson()).extract<Poco::JSON::Object::Ptr>());
	data.stringify(stream);
	return stream.str();
}

const CreateReservationResponse& CreateReservationResponse::operator =(const CreateReservationResponse &obj)
{
	_reservationUid = obj._reservationUid;
	_hotelUid = obj._hotelUid;
	_startDate = obj._startDate;
	_endDate = obj._endDate;
	_discount = obj._discount;
	_status = obj._status;
	_payment = obj._payment;
	return *this;
}
