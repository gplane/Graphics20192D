#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

//include shape, shader header files
#include "SDL_Start.h"
#include "Triangle.h"
#include "Circle.h"
#include "ShaderClass.h"
#include "SpaceShip.h"

// // GLEW - OpenGL Extension Wrangler - http://glew.sourceforge.net/
// // NOTE: include before SDL.h
#ifndef GLEW_H
#define GLEW_H
//#include <GL/glew.h>
#include "windows.h"

// SDL - Simple DirectMedia Layer - https://www.libsdl.org/
#ifndef SDL_H
#define SDL_H
#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
//#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

double currentTime = 0.0;

int main(int argc, char *argv[]) {
	//start and initialise SDL
	SDL_Start sdl;
	SDL_GLContext context = sdl.Init();

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	//*****************************************************
	//OpenGL specific data
	//create 10 circles
	float randValue, randValue2;
	srand(time(0));
	std::vector<Circle> circles;

	Triangle tri;

	for (int i = 0; i < 5; i++)
	{
		randValue = (float)rand() / RAND_MAX;
		randValue2 = (float)rand() / RAND_MAX;

		circles.push_back(Circle(0.2f, 0, 0));

		//circles.push_back(Circle(0.2f, (randValue-0.5f), (randValue2 -0.0f)));//Rand values set to zero
	}

	//create shaders
	Shader vSh("..//..//Assets//Shaders//shader.vert");
	Shader fSh("..//..//Assets//Shaders//shader.frag");

	//create, allocate and compile shaders
	//compile the shader code
	//1 for vertex, 2 for fragment - there is probably a better way to do this
	vSh.getShader(1);
	fSh.getShader(2);

	//create shader program, attach shaders together in the shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vSh.shaderID);
	glAttachShader(shaderProgram, fSh.shaderID);
	glLinkProgram(shaderProgram);

	//delete shader source code pointers
	glDeleteShader(vSh.shaderID);
	glDeleteShader(fSh.shaderID);

	//OpenGL buffers
	//set buffers for the circles
	for (int q = 0; q < 5; q++)
	{
		circles[q].setBuffers();
	}
	
	//***********************************************

	SDL_Event event;
	bool windowOpen = true;

	bool minus = false;
	SpaceShip player(0.5, 0.0, 0);

	//*****************************
	//'game' loop
	while (windowOpen)
	{
		//Changes background colour black to red and back again.
		if (currentTime >= 1.0)
			minus = true;

		else if (currentTime < 0.0)
			minus = false;




		if (minus)
			currentTime -= 0.01;

		else
			currentTime += 0.01;



		//****************************
		// OpenGL calls.
		
		glClearColor(currentTime, 0.0f, 0.0f, 1);
		glClear(GL_COLOR_BUFFER_BIT); 

		//draw the circles
		//Use shader program we have compiled and linked
		glUseProgram(shaderProgram);

		//set to wireframe so we can see the circles
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		//tri.setBuffers();
		//tri.render();

		player.setBuffers();
		player.render();

		//render the circles
		/*for (int q = 0; q < 5; q++)
		{
			circles[q].render();
		}*/

		

		SDL_GL_SwapWindow(sdl.win);

		//*****************************
		//SDL handled input
		//Any input to the program is done here

		
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					windowOpen = false;
				}
			}
		

	}
	//****************************
	// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
	SDL_GL_DeleteContext(context);

	SDL_Quit();
	return 0;





}
#endif
#endif