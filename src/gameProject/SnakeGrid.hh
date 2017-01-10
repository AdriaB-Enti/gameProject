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
	void resetGrid();
	void placeApple();
	void placeSnake();
	void detectKeyboard();

	Snake getSnake();
	bool gameEnded();
	int currentScore();
	float timeLeft();
private:
	bool isInsideGrid(snakeCell cell);	//for checking if a cell is outside the grid
	Sint32 rows, columns;				//number of cells in a row / column
	Sint32 cellWidth, cellHeight;
	Sprite **gridCells;
	Snake snake;
	float snakeTimer;					//timer to control snake's speed
	Sint32 appleScore;
	int timeToUpdate, timeToComplete, initFood, foodIncrease;
	levelDetails lvlDetails;
	void updateGrid();
};
