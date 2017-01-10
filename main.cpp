//Adria Biarnes & Sergi Sin - 2nB
//Github Link: https://github.com/AdriaB-Enti/gameProject
#include <string>		// Needed to process error messages
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_ttf.h>	// Used for loading fonts and rendering text
#include <SDL_image.h>	// Used for loading and drawing sprites
#include <rapidxml_utils.hpp>
#include <iostream>
#include "Button.h"

#include "GameEngine.hh"

const int WIDTH{ 1080 }, HEIGHT{ 720 }; // Define Window
int multipliers[5];

int main(int, char*[]) {

	GameEngine::Run<WIDTH, HEIGHT>("Snake"); //Start The Game
	
	return 0;
}