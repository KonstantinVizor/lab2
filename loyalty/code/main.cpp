#include "./inc/app/App.h"

int main(int argc, char **argv)
{
	int exitcode;
	App app;
	app.setPort(8080);
	exitcode = app.run(argc, argv);
	return exitcode;
}
