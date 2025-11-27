#include "../../inc/app/App.h"
#include "Poco/Data/Session.h"
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Util/Application.h>
#include <cstdio>
#include <memory>
#include "../../inc/repositories/PaymentRepository.h"
#include "../../inc/creator/Creator.h"
#include "../../inc/controllerFactory/ControllerFactory.h"
#include "../../inc/controllers/DefaultController.h"
#include "../../inc/controllers/payment/CreateController.h"
//#include "../../inc/controllers/payment/DeleteByUidController.h"
//#include "../../inc/controllers/payment/GetAllController.h"
#include "../../inc/controllers/payment/GetByUidController.h"
#include "../../inc/controllers/payment/UpdateByUidController.h"
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
	std::shared_ptr<Poco::Data::Session> session = std::make_shared<Poco::Data::Session>("postgresql", "host=postgres port=5432 dbname=payments user=program password=test");
	std::shared_ptr<PaymentRepository> paymentRepository = std::make_shared<PaymentRepository>();
	paymentRepository->setSession(session);
	Creator creator;
	ControllerFactory *factory = new ControllerFactory;
//	factory->registerHandler("/payment/all", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Payment::GetAllController>(paymentRepository));
	factory->registerHandler("/payment", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Payment::GetByUidController>(paymentRepository));
	factory->registerHandler("/payment", "PATCH", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Payment::UpdateByUidController>(paymentRepository));
	factory->registerHandler("/payment", "POST", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Payment::CreateController>(paymentRepository));
//	factory->registerHandler("/payment", "DELETE", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Payment::DeleteByUidController>(paymentRepository));
	factory->registerDefaultHandler(creator.getCreateFunction<Poco::Net::HTTPRequestHandler, DefaultController>());
	Poco::Net::HTTPServer server(factory, _port, new Poco::Net::HTTPServerParams);
	std::cout << "Payment started\n";
	std::cout.flush();
	server.start();
	this->waitForTerminationRequest();
	server.stop();
	return Poco::Util::Application::EXIT_OK;
}
