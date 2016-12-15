//Adria Biarnes & Sergi Sin
#include <string>		// Needed to process error messages
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_ttf.h>	// Used for loading fonts and rendering text
#include <SDL_image.h>	// Used for loading and drawing sprites
#include <rapidxml_utils.hpp>
#include <iostream>
#include "Button.h"


#include "Engine.h";


const int WIDTH{ 640 }, HEIGHT{ 480 };
int multipliers[5];

enum Scenes
{
	MenuScene,
	gameScene
};

Scenes actualScene = MenuScene;

void loadXML(std::string difficulty) {
	rapidxml::file<> xmlFile("../../res/cfg/levelcfg.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *root_node = doc.first_node("levels");
	rapidxml::xml_node<> * difNode = root_node->first_node("difficulty");
	for (int i = 0; i < 3; i++)
	{
		if (difNode->first_attribute("mode")->value() == difficulty) {
			rapidxml::xml_node<> *multNode = difNode->first_node();
			for (int i = 0; i < 5; i++)
			{
				multipliers[i] = atoi(multNode->value());	//parse char* to int
				multNode = multNode->next_sibling();
			}
			break;
		}
		difNode = difNode->next_sibling();
	}
	
}

void showLoadedCfg() {
	std::cout << "--LOADED CONFIG--\n";
	std::cout << "Cells: " << multipliers[0] <<"r*" << multipliers[0] << "c\n";
	std::cout << "Time: " << multipliers[1] << "t\n";
	std::cout << "Snake speed: " << multipliers[2] << "z\n";
	std::cout << "Init food: " << multipliers[3] << "x\n";
	std::cout << "Init food incr: " << multipliers[4] << "y\n";
}

void init() {
	using namespace std::string_literals; // Enables to use an array of characters with an "s" at the end as an string literal
	// --- INIT ---
	SDL_Log("Game Project made by:\n- Adria Biarnes\n- Sergi Sin");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "Unable to initialize SDL subsystems"s;
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Unable to initialize SDL_image"s;
	if (TTF_Init() != 0) throw "Unable to initialize SDL_ttf"s;
}

void changeScene(std::string difficulty) {
	actualScene = gameScene;
	loadXML(difficulty);
	showLoadedCfg();
}

int main(int, char*[]) {

	GameEngine engine = GameEngine();

	//engine.run();

	using namespace std::string_literals; // Enables to use an array of characters with an "s" at the end as an string literal
	try {
		init();
		// --- WINDOW ---
		SDL_Window *window{ SDL_CreateWindow("Game Project",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN) };
		if (window == nullptr) throw "Unable to initialize the SDL_Window"s;

		// --- RENDERER ---
		SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
		if (renderer == nullptr) throw "Unable to initialize the SDL_Renderer"s;

		// --- SPRITES ---
		SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/gfx/background.jpg") };
		SDL_Rect bgRect{ 0, 0, WIDTH, HEIGHT };
		SDL_Texture *spritesheet{ IMG_LoadTexture(renderer, "../../res/gfx/snake_spritesheet.jpg") };
		SDL_Rect spRect{ 0, 0, 75, 50 };

		//Scene
		Button easyButton = Button(renderer, "Easy", WIDTH/2, HEIGHT/4);
		Button mediumButton = Button(renderer, "Medium", WIDTH/2,2*HEIGHT/4);
		Button hardButton = Button(renderer, "Hard", WIDTH/2, 3*HEIGHT/4);

		// --- GAME LOOP ---
		SDL_Event evnt;
		for (bool isRunning{ true }; isRunning;) {
			// HANDLE EVENTS
			while (SDL_PollEvent(&evnt)) {
				switch (evnt.type) {
				case SDL_QUIT:			isRunning = false; break;
				case SDL_MOUSEBUTTONDOWN: 
					if (actualScene == MenuScene) {
						if (easyButton.isInside(evnt.motion.x, evnt.motion.y)) {
							SDL_Log("loading easy...");
							changeScene("Easy");
						}
						if (mediumButton.isInside(evnt.motion.x, evnt.motion.y)) {
							SDL_Log("loading medium...");
							changeScene("Medium");
						}
						if (hardButton.isInside(evnt.motion.x, evnt.motion.y)) {
							SDL_Log("loading hard...");
							changeScene("Hard");
						}
					}
						break;
				default:;
				}
			}
			// DRAW
			SDL_RenderClear(renderer);
			if (actualScene == MenuScene) {
				SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);		//background
				easyButton.draw(renderer);
				mediumButton.draw(renderer);
				hardButton.draw(renderer);
			}
			else if (actualScene == gameScene)
			{
				SDL_RenderCopy(renderer, spritesheet, nullptr, &spRect);		//spritesheet
			}
			SDL_RenderPresent(renderer);
		}

		// --- DESTROY ---
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyTexture(spritesheet);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	catch (const std::string &msg) { // Catch exceptions and print them as an error msg box
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", ("Description: " + msg + "\nSDL Error:" + SDL_GetError()).c_str(), nullptr);
	}
	// --- EXIT ---
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}