#pragma once

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	// dimensiuni ecran, nume fereastra
	Display(int width, int height, const std::string& title);
	~Display();

	void Clear(float r, float g, float b, float a);
	void SwapBuffers();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

