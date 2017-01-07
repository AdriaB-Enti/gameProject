#pragma once
#include <ctime>
#include "SnakeGrid.hh"
#include "Snake.hh"

//BORRAR
#include "InputManager.hh"

SnakeGrid::SnakeGrid(Sint32 nrows, Sint32 ncols, Sint32 cellWidth, Sint32 cellHeight) : snake({ 1,1 })
{
	rows = nrows;
	columns = ncols;
	//crear grid
	gridCells = new Sprite*[nrows];						//create rows
	for (int i = 0; i < nrows; ++i) {
		gridCells[i] = new Sprite[ncols];				//create columns for every row
	}
	for (int row = 0; row < nrows; ++row) {				//inicialize grid
		for (int col = 0; col < ncols; ++col) {
			gridCells[row][col].transform = { cellWidth / 2 + cellWidth*row, 
				cellHeight/2 + cellHeight*col, cellWidth, cellHeight };	//x, y, w, h
			if (col == 0 || col == ncols - 1 || row == 0 || row == nrows-1) {
				gridCells[row][col].objectID = ObjectID::SNAKE_WALL;
			}
			else {
				gridCells[row][col].objectID = ObjectID::EMPTY_SNAKE;
			}
		}
	}
	srand(unsigned(time(nullptr)));						//in order to get random numbers
	placeApple();										//insert apple
}
// [0][1][2][3]
SnakeGrid::~SnakeGrid()
{

}

void SnakeGrid::Update()
{
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		placeApple();
	}
}

void SnakeGrid::Draw()
{
	
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < columns; ++col) {
			gridCells[row][col].Draw();
		}
	}
}

void SnakeGrid::reset()
{

}

Snake SnakeGrid::getSnake()
{
	return snake;
}

bool SnakeGrid::isOutsideGrid(snakeCell cell)
{
	//if()... return true
	return false;
}

void SnakeGrid::placeApple() {
	//random apple position
	int randCol = 1+rand()%(columns-2);
	//[0][1][2][3] -> cols=4
	int randRow = 1 + rand() % (rows - 2);

	gridCells[randRow][randCol].objectID = ObjectID::SNAKE_APLE;
}