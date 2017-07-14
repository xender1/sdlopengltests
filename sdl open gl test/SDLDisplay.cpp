#include "SDLDisplay.h"

#include <memory>
#include <SDL.h>
#include <GL\glew.h>
#include <stdio.h>
#include <string>

namespace Display {

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	//std::unique_ptr<SDL_Window> gWindow = NULL;

	//Event handler
	SDL_Event e;

	//OpenGL context
	SDL_GLContext gContext;

	//Graphics program
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

	//Main loop flag
	bool quit = false;

	//Render flag
	bool gRenderQuad = true;

	bool init()
	{
		//Initialization flag
		bool success = true;

		

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Use OpenGL 3.1 core
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Create context
				gContext = SDL_GL_CreateContext(gWindow);
				if (gContext == NULL)
				{
					printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize GLEW
					glewExperimental = GL_TRUE;
					GLenum glewError = glewInit();
					if (glewError != GLEW_OK)
					{
						printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
					}

					//Use Vsync
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					}

					//Initialize OpenGL
					if (!initGL())
					{
						printf("Unable to initialize OpenGL!\n");
						success = false;
					}
				}
			}
		}

		return success;
	}

	bool initGL()
	{
		//Success flag
		bool success = true;

		//Generate program
		gProgramID = glCreateProgram();

		//Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Get vertex source
		const GLchar* vertexShaderSource[] =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};

		//Set vertex source
		glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

		//Compile vertex source
		glCompileShader(vertexShader);

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
		if (vShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile vertex shader %d!\n", vertexShader);
			//printShaderLog(vertexShader);
			success = false;
		}
		else
		{
			//Attach vertex shader to program
			glAttachShader(gProgramID, vertexShader);


			//Create fragment shader
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			//Get fragment source
			const GLchar* fragmentShaderSource[] =
			{
				"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
			};

			//Set fragment source
			glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

			//Compile fragment source
			glCompileShader(fragmentShader);

			//Check fragment shader for errors
			GLint fShaderCompiled = GL_FALSE;
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
			if (fShaderCompiled != GL_TRUE)
			{
				printf("Unable to compile fragment shader %d!\n", fragmentShader);
				//printShaderLog(fragmentShader);
				success = false;
			}
			else
			{
				//Attach fragment shader to program
				glAttachShader(gProgramID, fragmentShader);


				//Link program
				glLinkProgram(gProgramID);

				//Check for errors
				GLint programSuccess = GL_TRUE;
				glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
				if (programSuccess != GL_TRUE)
				{
					printf("Error linking program %d!\n", gProgramID);
					//printProgramLog(gProgramID);
					success = false;
				}
				else
				{
					//Get vertex attribute location
					gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
					if (gVertexPos2DLocation == -1)
					{
						printf("LVertexPos2D is not a valid glsl program variable!\n");
						success = false;
					}
					else
					{
						//Initialize clear color
						glClearColor(0.f, 0.f, 0.f, 1.f);

						//VBO data
						GLfloat vertexData[] =
						{
							-0.5f, -0.5f,
							0.5f, -0.5f,
							0.5f,  0.9f,
							-0.5f,  0.5f
						};

						//IBO data
						GLuint indexData[] = { 0, 1, 2, 3 };
						/*
						//Create VBO
						glGenBuffers(1, &gVBO);
						glBindBuffer(GL_ARRAY_BUFFER, gVBO);
						glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

						//Create IBO
						glGenBuffers(1, &gIBO);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
						glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
						*/
					}
				}
			}
		}

		return success;

	}

	void close()
	{
		//Deallocate program
		glDeleteProgram(gProgramID);

		//Destroy window	
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;

		//Quit SDL subsystems
		SDL_Quit();
	}

	bool isOpen()
	{
		return !quit;
	}

	void clear()
	{
		//Clear color buffer
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void render()
	{
		/*
		if (gRenderQuad)
		{
			//Bind program
			glUseProgram(gProgramID);

			//Enable vertex position
			glEnableVertexAttribArray(gVertexPos2DLocation);

			//Set vertex data
			glBindBuffer(GL_ARRAY_BUFFER, gVBO);
			glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

			//Set index data and render
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
			glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

			//Disable vertex position
			glDisableVertexAttribArray(gVertexPos2DLocation);

			//Unbind program
			glUseProgram(NULL);
		}
		*/
		//Update screen
		SDL_GL_SwapWindow(gWindow);
	}

	void handleEvent()
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			//Handle keypress with current mouse position
			else if (e.type == SDL_TEXTINPUT)
			{
				int x = 0, y = 0;
				SDL_GetMouseState(&x, &y);
				//handleKeys(e.text.text[0], x, y);
				if (e.text.text[0] == 'q')
				{
					gRenderQuad = !gRenderQuad;
				}
			}
		}
	}

}