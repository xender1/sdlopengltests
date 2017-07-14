/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#include "SDLDisplay.h"
#include "Application.h"
#include <stdio.h>

int main(int argc, char* args[])
{

	if (!Display::init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		Application app;
		app.runMainGameLoop();
	}

	return 0;
}
