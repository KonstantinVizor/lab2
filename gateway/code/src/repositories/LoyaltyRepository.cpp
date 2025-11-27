#include "../../inc/repositories/LoyaltyRepository.h"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <algorithm>

LoyaltyRepository::LoyaltyRepository(const std::string &path) :
							_path(path)
{}

LoyaltyInfo LoyaltyRepository::getByUsername(const std::string &username)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	LoyaltyModel model;
	LoyaltyInfo info;
	std::string json = "", tmp;
	req.setURI("/loyalty");
	client.setHost(_path);
	client.setPort(8080);
	req.set("X-User-Name", username);
	req.setMethod("GET");
	client.sendRequest(req);
	std::istream &stream = client.receiveResponse(resp);
	while (stream >> tmp)
		json += tmp;
	model.fromJson(json, true);
	info = LoyaltyInfo(model);
	return info;
}

#include <iostream>

void LoyaltyRepository::updateByUsername(const std::string &username, const LoyaltyModel &model)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	std::string uri = "/loyalty";
	req.setURI(uri);
	req.set("X-User-Name", username);
	client.setHost(_path);
	client.setPort(8080);
	req.setMethod("PATCH");
	req.setContentType("application/json");
	req.setContentLength(model.toJson().size());
	client.sendRequest(req) << model.toJson();
	client.receiveResponse(resp);
}
