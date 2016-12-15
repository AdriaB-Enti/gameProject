#pragma once
#include <SDL_render.h>

#define Rend Renderer::Instance()

class Renderer
{
public:
	Renderer();
	~Renderer();
	Renderer static &Instance();
private:
	SDL_Renderer* mySDLRenderer{ nullptr };
};

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(mySDLRenderer);
}

Renderer & Renderer::Instance()
{
	static Renderer renderer;
	return renderer;
}
