#include "../../inc/repositories/HotelRepository.h"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/Net/NetException.h>
#include <exception>
#include <istream>
#include <string>
#include <vector>
#include "../../inc/models/ReservationWithHotel.h"
#include "Poco/JSON/Array.h"

HotelRepository::HotelRepository(const std::string &path) :
					_path(path)
{}

PaginationResponce HotelRepository::getHotelAll(uint32_t offset, uint32_t limit)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	PaginationResponce result;
	std::string json = "";
	std::string tmp;
	req.setURI("/hotel/all?page=" + std::to_string(offset) + "&size=" + std::to_string(limit));
	client.setHost(_path);
	client.setPort(8080);
	req.setMethod("GET");
	client.sendRequest(req);
	std::istream &stream = client.receiveResponse(resp);
	while (stream >> tmp)
		json += (tmp + ' ');
	result.fromJson(json);
	return result;
}

HotelResponce HotelRepository::getHotelByUid(const std::string &uid)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	HotelResponce result;
	std::string json = "";
	std::string tmp;
	req.setURI("/hotel?hotel_uid=" + uid);
	req.setMethod("GET");
	client.setHost(_path);
	client.setPort(8080);
	client.sendRequest(req);
	std::istream &stream = client.receiveResponse(resp);
	while (stream >> tmp)
		json += (tmp + ' ');
	result.fromJson(json);
	return result;
}

std::vector<ReservationWithHotel> HotelRepository::getReservationsByUsername(const std::string &username)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	std::vector<ReservationWithHotel> result;
	std::string json = "", tmp;
	req.setURI("/reservation");
	req.set("X-User-Name", username);
	req.setMethod("GET");
	client.setHost(_path);
	client.setPort(8080);
	client.sendRequest(req);
	std::istream &stream = client.receiveResponse(resp);
	while (stream >> tmp)
		json += (tmp + ' ');
	Poco::JSON::Parser parser;
	Poco::JSON::Array::Ptr arr = parser.parse(json).extract<Poco::JSON::Array::Ptr>();
	result = std::vector<ReservationWithHotel>(arr->size());
	for (uint32_t i = 0; i < arr->size(); i++)
		result[i].fromJson(arr->get(i).toString(), true);
	return result;
}

#include <iostream>

ReservationWithHotel HotelRepository::createReservation(const std::string &username, const CreateReservationRequest &request)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	ReservationWithHotel model;
	std::string json = "", tmp;
	req.setURI("/reservation");
	client.setHost(_path);
	client.setPort(8080);
	req.setMethod("POST");
	req.set("X-User-Name", username);
	req.setContentType("application/json");
	req.setContentLength(request.toJson().size());
	client.sendRequest(req) << request.toJson();
	std::istream &stream = client.receiveResponse(resp);
	while (stream >> tmp)
		json += (tmp + ' ');
	model.fromJson(json);
	return model;
}

void HotelRepository::updateReservation(const std::string &uid, const ReservationWithHotel &res)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	req.setURI("/reservation?reservation_uid=" + uid);
	client.setHost(_path);
	client.setPort(8080);
	req.setMethod("PATCH");
	req.setContentType("application/json");
	req.setContentLength(res.toJson().size());
	client.sendRequest(req) << res.toJson();
	client.receiveResponse(resp);
}

void HotelRepository::deleteReservation(const std::string &uid)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	req.setURI("/reservation?reservation_uid=" + uid);
	client.setHost(_path);
	client.setPort(8080);
	req.setMethod("DELETE");
	req.setContentType("application/json");
	client.sendRequest(req);
	client.receiveResponse(resp);
}
