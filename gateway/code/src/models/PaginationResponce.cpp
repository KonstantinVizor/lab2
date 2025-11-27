#include "../../inc/models/PaginationResponce.h"
#include <string>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

PaginationResponce::PaginationResponce(const PaginationResponce &obj) :
								_pageNumber(obj._pageNumber),
								_pageSize(obj._pageSize),
								_hotels(obj._hotels)
{}

PaginationResponce::PaginationResponce(PaginationResponce &&obj) :
								_pageNumber(obj._pageNumber),
								_pageSize(obj._pageSize),
								_hotels(obj._hotels)
{}

uint32_t PaginationResponce::getPageNumber() const
{
	return _pageNumber;
}

uint32_t PaginationResponce::getPageSize() const
{
	return _pageSize;
}

const std::vector<HotelResponce>& PaginationResponce::getHotels() const
{
	return _hotels;
}

PaginationResponce& PaginationResponce::setPageNumber(uint32_t pageNumber)
{
	_pageNumber = pageNumber;
	return *this;
}

PaginationResponce& PaginationResponce::setPageSize(uint32_t pageSize)
{
	_pageSize = pageSize;
	return *this;
}

PaginationResponce& PaginationResponce::setHotels(const std::vector<HotelResponce> &hotels)
{
	_hotels = hotels;
	return *this;
}

bool PaginationResponce::fromJson(const std::string &json, bool all)
{
	Poco::Dynamic::Var var;
	Poco::JSON::Parser parser;
	Poco::JSON::Object::Ptr data;
	try
	{
		data = parser.parse(json).extract<Poco::JSON::Object::Ptr>();
		var = data->get("page");
		if (!var.isEmpty())
			_pageNumber = std::stoi(var.toString());
		else if (all)
			return false;
		var = data->get("pageSize");
		if (!var.isEmpty())
			_pageSize = std::stoi(var.toString());
		else if (all)
			return false;
		var = data->get("totalElements");
		if (!var.isEmpty())
			_hotels = std::vector<HotelResponce>(std::stoi(var.toString()));
		else if (all)
			return false;
		var = data->get("items");
		Poco::JSON::Array::Ptr arr = var.extract<Poco::JSON::Array::Ptr>();
		for (uint32_t i = 0; i < arr->size(); i++)
		{
			HotelResponce tmp;
			if (!tmp.fromJson(arr->get(i).toString()))
				return false;
			_hotels[i] = tmp;
		}
	}
	catch (...)
	{
		return false;
	}
	return {};
}

std::string PaginationResponce::toJson() const
{
	std::ostringstream stream;
	Poco::JSON::Object data;
	Poco::JSON::Parser parser;
	Poco::JSON::Array arr;
	for (uint32_t i = 0; i < _hotels.size(); i++)
		arr.add(parser.parse(_hotels[i].toJson()).extract<Poco::JSON::Object::Ptr>());
	data.set("page", _pageNumber);
	data.set("pageSize", _pageSize);
	data.set("totalElements", _hotels.size());
	data.set("items", arr);
	data.stringify(stream);
	return stream.str();
}

const PaginationResponce& PaginationResponce::operator =(const PaginationResponce &obj)
{
	_pageNumber = obj._pageNumber;
	_pageSize = obj._pageSize;
	_hotels = obj._hotels;
	return *this;
}
