#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>	// Used for loading fonts and rendering text

class Button
{
public:
	Button(SDL_Renderer * renderer, const char* text, int posX, int posY);
	~Button();
	bool isInside(Sint32 x, Sint32 y);
	void draw(SDL_Renderer * renderer);
	void setActive(bool activeState);
private:
	SDL_Texture *textTexture;
	SDL_Rect textRect;
	bool isActive;
};


Button::Button(SDL_Renderer * renderer, const char* text, int posX, int posY)
{
	TTF_Font *font{ TTF_OpenFont("../../res/fnt/arial.ttf", 50) };
	if (font == nullptr) throw "Unable to initialize the TTF_Font";
	SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, text, SDL_Color{ 255, 0, 0, 255 }) };
	if (tmpSurf == nullptr) TTF_CloseFont(font), throw "Unable to create the SDL text surface";
	textTexture = { SDL_CreateTextureFromSurface(renderer, tmpSurf) };
	textRect = { posX - (tmpSurf->w >> 1),
		posY - (tmpSurf->h >> 1),
		tmpSurf->w, tmpSurf->h };
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);
	isActive = true;
}

Button::~Button()
{
	SDL_DestroyTexture(textTexture);
}

bool Button::isInside(Sint32 x, Sint32 y)
{
	if (isActive && x >= textRect.x && x <= textRect.x+textRect.w && y >= textRect.y && y <= textRect.y+textRect.h) {
		return true;
	}
	return false;
}

void Button::draw(SDL_Renderer * renderer) {
	if (isActive) {
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	}
}

void Button::setActive(bool activeState) {
	isActive = activeState;
}