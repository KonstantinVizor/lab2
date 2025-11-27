#include "../../inc/repositories/PaymentRepository.h"
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPClientSession.h>
#include <exception>
#include "../../inc/uri/Uri.h"
#include "Poco/Net/NetException.h"

PaymentRepository::PaymentRepository(const std::string &path) :
							_path(path)
{}

PaymentInfo PaymentRepository::getByUid(const std::string &uid)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	PaymentModel model;
	PaymentInfo info;
	std::string json = "", tmp;
	req.setURI("/payment?payment_uid=" + uid);
	client.setHost(_path);
	client.setPort(8080);
	req.setMethod("GET");
	client.sendRequest(req);
	std::istream &stream = client.receiveResponse(resp);
	while (stream >> tmp)
		json += tmp;
	model.fromJson(json, true);
	info.setStatus(model.getStatus())
		.setPrice(model.getPrice());
	return info;
}

void PaymentRepository::updateByUid(const std::string &uid, const PaymentModel &model)
{
	Poco::Net::HTTPResponse resp;
	Poco::Net::HTTPRequest req;
	Poco::Net::HTTPClientSession client;
	req.setURI("/payment?payment_uid=" + uid);
	client.setHost(_path);
	client.setPort(8080);
	req.setContentType("application/json");
	req.setContentLength(model.toJson().size());
	req.setMethod("PATCH");
	client.sendRequest(req) << model.toJson();
	client.receiveResponse(resp);
}

#include <iostream>

std::string PaymentRepository::create(const PaymentModel &model)
{
	try
	{
		Poco::Net::HTTPResponse resp;
		Poco::Net::HTTPRequest req;
		Poco::Net::HTTPClientSession client;
		req.setURI("/payment");
		client.setHost(_path);
		client.setPort(8080);
		req.setMethod("POST");
		req.setContentType("application/json");
		req.setContentLength(model.toJson().size());
		client.sendRequest(req) << model.toJson();
		client.receiveResponse(resp);
		std::cout << resp.getStatus() << " " << resp.getReason() << "\n";
		Uri uri(resp.get("location"));
		return uri.getValue("payment_uid");
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
	}
}
