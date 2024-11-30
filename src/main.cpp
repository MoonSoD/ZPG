#include <stdlib.h>
#include <stdio.h>
#include "App.h"

int main(void)
{
	App* app = new App();
	app->init();

	app->createScenes();

	app->run();
}