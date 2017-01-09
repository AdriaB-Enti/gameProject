#pragma once
#include "Sprite.hh"
#include "Snake.hh"
#include "LevelDetails.hh"

class SnakeGrid
{
public:
	SnakeGrid(Sint32 cellWidth, Sint32 cellHeight);
	~SnakeGrid();
	void start(std::string difStr);
	void Update();
	void Draw();
	void reset();
	Snake getSnake();
	void placeApple();
	void placeSnake();
	void detectKeyboard();
	//void loadLvl(difficulty dif);
private:
	bool isInsideGrid(snakeCell cell);	//for checking if a cell is outside the grid
	Sint32 rows, columns;			//number of cells in a row / column
	Sint32 cellWidth, cellHeight;
	//no sé si per la Grid lo millor seria fer un doble punter com el Jordi, o una llista, o un diccionari (posicio-Sprite)...
	Sprite **gridCells;
	//estructura da dades per les pomes?
	//estructura de dades per els obstacles?
	Snake snake;
	float timer;		//timer to control snake's speed
	//float 
	Sint32 score, lives;
	//level dependent vars:
	Sint32 appleScore;
	int timeToUpdate, timeToComplete, initFood, foodIncrease;
	levelDetails lvlDetails;
};
