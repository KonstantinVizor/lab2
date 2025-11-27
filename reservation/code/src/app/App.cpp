#include "../../inc/app/App.h"
#include "Poco/Data/Session.h"
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Util/Application.h>
#include <cstdio>
#include <memory>
#include "../../inc/repositories/ReservationRepository.h"
#include "../../inc/repositories/HotelRepository.h"
#include "../../inc/creator/Creator.h"
#include "../../inc/controllerFactory/ControllerFactory.h"
#include "../../inc/controllers/DefaultController.h"
#include "../../inc/controllers/reservation/CreateController.h"
#include "../../inc/controllers/reservation/DeleteByUidController.h"
//#include "../../inc/controllers/reservation/GetAllController.h"
//#include "../../inc/controllers/reservation/GetByUidController.h"
#include "../../inc/controllers/reservation/GetByUsernameController.h"
#include "../../inc/controllers/reservation/UpdateByUidController.h"
#include "../../inc/controllers/hotel/GetAllController.h"
#include "../../inc/controllers/hotel/GetByUidController.h"
#include "../creator/Creator.hpp"

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
	Poco::Data::PostgreSQL::Connector::registerConnector();
	std::shared_ptr<Poco::Data::Session> session = std::make_shared<Poco::Data::Session>("postgresql", "host=postgres port=5432 dbname=reservations user=program password=test");
	std::shared_ptr<ReservationRepository> reservationRepository = std::make_shared<ReservationRepository>();
	std::shared_ptr<HotelRepository> hotelRepository = std::make_shared<HotelRepository>();
	reservationRepository->setSession(session);
	hotelRepository->setSession(session);
	Creator creator;
	ControllerFactory *factory = new ControllerFactory;
	factory->registerHandler("/hotel/all", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Hotel::GetAllController>(hotelRepository));
	factory->registerHandler("/hotel", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Hotel::GetByUidController>(hotelRepository));
//	factory->registerHandler("/reservation/{s}", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Reservation::GetByUidController>(reservationRepository,
//																			hotelRepository));
	factory->registerHandler("/reservation", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Reservation::GetByUsernameController>(reservationRepository,
																			hotelRepository));
	factory->registerHandler("/reservation", "POST", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Reservation::CreateController>(reservationRepository,
																			hotelRepository));
	factory->registerHandler("/reservation", "PATCH", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Reservation::UpdateByUidController>(reservationRepository));
	factory->registerHandler("/reservation", "DELETE", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Reservation::DeleteByUidController>(reservationRepository));
	factory->registerDefaultHandler(creator.getCreateFunction<Poco::Net::HTTPRequestHandler, DefaultController>());
	Poco::Net::HTTPServer server(factory, _port, new Poco::Net::HTTPServerParams);
	std::cout << "Reservation started\n";
	std::cout.flush();
	server.start();
	this->waitForTerminationRequest();
	server.stop();
	return Poco::Util::Application::EXIT_OK;
}
