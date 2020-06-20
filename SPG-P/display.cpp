#include <iostream>
#include <GL/glew.h>
#include "display.h"


Display::Display(int width, int height, const std::string& title)
{
	std::cout << "Display()\n";

	// imi fac fereastra in care voi desena
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);  // cel putin 8 biti pentru rosu
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);  
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);  // 16 e si valoarea default
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // aloca spatiu pentru 2 ferestre, vezi Swap Buffers

	// SDL_CreateWindow e scris in C, astfel ca nu accepta string 
	// SDL trimite comenzi la OS care genereaza Windowul care ne e prezentat aici
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	// Cu OpenGl vom desenea, astfel ca OS va trece datele prin GPU inainte de a desena
	// Cumva ii dau acces codului scris in OpenGL asupra ferestrei
	m_glContext = SDL_GL_CreateContext(m_window);

	// parte de OpenGL
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cout << "Glew failed to initialize! \n";
	}

	// z-index
	glEnable(GL_DEPTH_TEST);

	// sa nu mai deseneze fetele care nu sunt spre noi, suficient doar pentru obiecte convexe, a rezolvat cubul
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

Display::~Display()
{
	// dealocare in ordine inversa
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	std::cout << "~Display()\n";
	SDL_Quit();
}



void Display::SwapBuffers()
{
	// OpenGL creaza a doua fereastra in timp ce noi vedem vechiul frame
	// nu se afiseaza chestii pana nu s-au desenat
	SDL_GL_SwapWindow(m_window);
}


// seteaza o culoare si pune pe ecran (in principiu ca background)
void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	// golesc si depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// placa video doar primeste date, nu are un format anume
// apoi le proceseaza intr-un format anume in paralel (vertex shader)
// rezulta puncte (care vor forma un triunghi)
// apoi rasterizarea in paralel, conecteaza punctele si umple aria
// apoi iar procesare (ia fiecare pixel si le da culoare)  (fragment shader)
// rezulta imaginea pe care o transmite la ecran