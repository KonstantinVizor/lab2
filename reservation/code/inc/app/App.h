#ifndef __APP_H__
#define __APP_H__

#include <Poco/Util/ServerApplication.h>

class App : public Poco::Util::ServerApplication
{
	private:
		int _port;

	protected:
		virtual int main(const std::vector<std::string> &args) override;

	public:	
		virtual ~App() override = default;
		explicit App(const App &) = delete;
		App(App &&) = delete;
		App();

		App& setPort(int port);
};

#endif
