//Adria Biarnes & Sergi Sin - 2nB
//Github Link: https://github.com/AdriaB-Enti/gameProject
#include <string>		// Needed to process error messages
#include <SDL.h>		// Always needs to be included for an SDL app
#include "GameEngine.hh"

const int WIDTH{ 1080 }, HEIGHT{ 720 };			// Define Window

int main(int, char*[]) {

	GameEngine::Run<WIDTH, HEIGHT>("Snake");	//Start The Game
	
	return 0;
}