#pragma once

#include <SDL.h>
#include <string>


#define W Window::Instance()

class Window
{
public:
	Window();
	~Window();
	Window static &Instance(std::string &&name, int &&screenWidth, int &&screenHeight);
private:
	SDL_Window* mySDLWindow{ nullptr };
	const int screenWidth, screenHeight;
	const std::string wName;
};

Window::Window()
{

}

Window::~Window()
{
	
}

inline Window & Window::Instance(std::string &&name = "", int &&screenWidth = 0, int &&screenHeight = 0)
{
	static Window window(std::move(name), std::move(screenWidth), std::move(screenHeight));
	return window;
}
