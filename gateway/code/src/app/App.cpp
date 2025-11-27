#include "../../inc/app/App.h"
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Util/Application.h>
#include <cstdio>
#include <memory>
#include "../../inc/repositories/PaymentRepository.h"
#include "../../inc/repositories/LoyaltyRepository.h"
#include "../../inc/repositories/HotelRepository.h"
#include "../../inc/creator/Creator.h"
#include "../../inc/controllerFactory/ControllerFactory.h"
#include "../../inc/controllers/DefaultController.h"
#include "../../inc/controllers/HotelGetAllController.h"
#include "../../inc/controllers/LoyaltyGetByUsernameController.h"
#include "../../inc/controllers/MeGetByUsernameController.h"
#include "../../inc/controllers/ReservationCreateByUsernameController.h"
#include "../../inc/controllers/ReservationDeleteByUsernameNUidController.h"
#include "../../inc/controllers/ReservationGetByUsernameController.h"
#include "../../inc/controllers/ReservationGetByUsernameNUidController.h"
#include "../creator/Creator.hpp"
#include <iostream>

App::App() : 
	_port(8080)
{}

App& App::setPort(int port)
{
	_port = port;
	return *this;
}

int App::main([[maybe_unused]] const std::vector<std::string> &args)
{
	std::setbuf(stdout, NULL);
	std::shared_ptr<PaymentRepository> paymentRepository = std::make_shared<PaymentRepository>("payment");
	std::shared_ptr<LoyaltyRepository> loyaltyRepository = std::make_shared<LoyaltyRepository>("loyalty");
	std::shared_ptr<HotelRepository> hotelRepository = std::make_shared<HotelRepository>("reservation");
	Creator creator;
	ControllerFactory *factory = new ControllerFactory;
	factory->registerHandler("/api/v1/hotels", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, HotelGetAllController>(hotelRepository));
	factory->registerHandler("/api/v1/me", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, MeGetByUsernameController>(hotelRepository,
																	loyaltyRepository,
																	paymentRepository)); // *
	factory->registerHandler("/api/v1/reservations", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, 
												ReservationGetByUsernameController>(hotelRepository,
																	paymentRepository)); // * 
	factory->registerHandler("/api/v1/reservations", "POST", creator.getCreateFunction<Poco::Net::HTTPRequestHandler,
												ReservationCreateByUsernameController>(hotelRepository,
																	paymentRepository,
																	loyaltyRepository)); // *
	factory->registerHandler("/api/v1/reservations/{s}", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler,
												ReservationGetByUsernameNUidController>(hotelRepository,
																	paymentRepository)); // *
	factory->registerHandler("/api/v1/reservations/{s}", "DELETE", creator.getCreateFunction<Poco::Net::HTTPRequestHandler,
												ReservationDeleteByUsernameController>(hotelRepository,
																	loyaltyRepository,
																	paymentRepository)); // *
	factory->registerHandler("/api/v1/loyalty", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, LoyaltyGetByUsernameController>(loyaltyRepository)); // *
	factory->registerDefaultHandler(creator.getCreateFunction<Poco::Net::HTTPRequestHandler, DefaultController>());
	std::cout << "Gateway started\n";
	std::cout.flush();
	Poco::Net::HTTPServer server(factory, _port, new Poco::Net::HTTPServerParams);
	server.start();
	this->waitForTerminationRequest();
	server.stop();
	return Poco::Util::Application::EXIT_OK;
}
