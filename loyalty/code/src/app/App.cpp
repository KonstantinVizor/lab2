#include "../../inc/app/App.h"
#include "Poco/Data/Session.h"
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Util/Application.h>
#include <memory>
#include "../../inc/repositories/LoyaltyRepository.h"
#include "../../inc/creator/Creator.h"
#include "../../inc/controllerFactory/ControllerFactory.h"
#include "../../inc/controllers/DefaultController.h"
//#include "../../inc/controllers/loyalty/CreateController.h"
//#include "../../inc/controllers/loyalty/DeleteByUsernameController.h"
//#include "../../inc/controllers/loyalty/GetAllController.h"
#include "../../inc/controllers/loyalty/GetByUsernameController.h"
#include "../../inc/controllers/loyalty/UpdateByUsernameController.h"
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
	std::shared_ptr<Poco::Data::Session> session = std::make_shared<Poco::Data::Session>("postgresql", "host=postgres port=5432 dbname=loyalties user=program password=test");
	std::shared_ptr<LoyaltyRepository> loyaltyRepository = std::make_shared<LoyaltyRepository>();
	loyaltyRepository->setSession(session);
	Creator creator;
	ControllerFactory *factory = new ControllerFactory;
//	factory->registerHandler("/loyalty/all", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Loyalty::GetAllController>(loyaltyRepository));
//	factory->registerHandler("/loyalty", "POST", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Loyalty::CreateController>(loyaltyRepository));
//	factory->registerHandler("/loyalty", "DELETE", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Loyalty::DeleteByUsernameController>(loyaltyRepository));
	factory->registerHandler("/loyalty", "GET", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Loyalty::GetByUsernameController>(loyaltyRepository));
	factory->registerHandler("/loyalty", "PATCH", creator.getCreateFunction<Poco::Net::HTTPRequestHandler, Loyalty::UpdateByUsernameController>(loyaltyRepository));
	factory->registerDefaultHandler(creator.getCreateFunction<Poco::Net::HTTPRequestHandler, DefaultController>());
	Poco::Net::HTTPServer server(factory, _port, new Poco::Net::HTTPServerParams);
	std::cout << "Loyalty started\n";
	std::cout.flush();
	server.start();
	this->waitForTerminationRequest();
	server.stop();
	return Poco::Util::Application::EXIT_OK;
}
