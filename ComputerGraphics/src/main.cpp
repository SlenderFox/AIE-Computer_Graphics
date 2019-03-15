#include "Project3D.h"

int main()
{
	auto app = new Project3D();

	app->run("Project 3D", 1280, 720, false);

	delete app;
	
	return 0;
}