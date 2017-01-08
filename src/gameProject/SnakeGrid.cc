#pragma once
#include <ctime>
#include "SnakeGrid.hh"
#include "Snake.hh"
#include "InputManager.hh"
#include "TimeManager.hh"

#define updateTime 200

SnakeGrid::SnakeGrid(Sint32 nrows, Sint32 ncols, Sint32 ncellWidth, Sint32 ncellHeight) : snake({ 1,3 })
{
	rows = nrows+2;										//2 extra cells for borders on left and right
	columns = ncols+2;									//same for columns
	cellWidth = ncellWidth;
	cellHeight = ncellHeight;
	//creating the grid:
	gridCells = new Sprite*[rows];						//create rows
	for (int i = 0; i < rows; ++i) {
		gridCells[i] = new Sprite[columns];				//create columns for every row
	}

	reset();											//inicialize grid

	appleScore = 100;
}

SnakeGrid::~SnakeGrid()
{

}

void SnakeGrid::Update()
{
	detectKeyboard();
	timer += TM.GetDeltaTime();
	if (timer > updateTime)
	{
		timer = 0;
		snakeCell nextCell = snake.nextPosition();
		ObjectID cellID = gridCells[nextCell.x][nextCell.y].objectID;

		if (isInsideGrid(nextCell) && (cellID == ObjectID::EMPTY_SNAKE 
				|| cellID == ObjectID::SNAKE_APLE)) {		//only move snake if next position is empty or an apple
			if (cellID == ObjectID::SNAKE_APLE)						//if it's an apple, add score, place a new one, grow snake
				{
					score += appleScore;
					placeApple();
					snake.growUp();
				}
				gridCells[snake.getHead().x][snake.getHead().y].objectID = ObjectID::SNAKE_BODY;
				snake.Update();
				gridCells[snake.getHead().x][snake.getHead().y].objectID = ObjectID::SNAKE_HEAD;
				gridCells[snake.getTail().x][snake.getTail().y].objectID = ObjectID::SNAKE_TAIL;
				if (snake.hasMoved()) {						//if snake has moved the tail, clear tail cell
					gridCells[snake.prevTail().x][snake.prevTail().y].objectID = ObjectID::EMPTY_SNAKE;
				}
			
		}
		else {
			reset();
		}
	}
	if (IM.IsKeyDown<'l'>()) {	//BORRAR
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
	for (int row = 0; row < rows; ++row) {				//inicialize grid
		for (int col = 0; col < columns; ++col) {
			gridCells[row][col].transform = { cellWidth / 2 + cellWidth*row,
				cellHeight / 2 + cellHeight*col, cellWidth, cellHeight };	//x, y, w, h
			if (col == 0 || col == columns - 1 || row == 0 || row == rows - 1) {
				gridCells[row][col].objectID = ObjectID::SNAKE_WALL;
			}
			else {
				gridCells[row][col].objectID = ObjectID::EMPTY_SNAKE;
			}
		}
	}
	srand(unsigned(time(nullptr)));						//in order to get random numbers
	snake = Snake({ 1,3 });
	placeSnake();
	placeApple();										//insert apple
	timer = 0;
	score = 0;
}

Snake SnakeGrid::getSnake()
{
	return snake;
}
//[0][1][2][3] -> width 4
bool SnakeGrid::isInsideGrid(snakeCell cell)		//returns true if given cell is inside the grid (without touching the borders)
{
	if (cell.x > 0 && cell.x < rows-1 && cell.y > 0 && cell.y < columns - 1) {
		return true;
	}
	return false;
}

void SnakeGrid::placeApple() {	//TODO: COMPROVAR QUE LA CASELLA ESTÀ BUIDA
	//random apple position
	int randCol = 1+rand()%(columns-2);
	//[0][1][2][3] -> cols=4
	int randRow = 1 + rand() % (rows - 2);

	gridCells[randRow][randCol].objectID = ObjectID::SNAKE_APLE;
}

void SnakeGrid::placeSnake()
{
	gridCells[snake.getHead().x][snake.getHead().y].objectID = ObjectID::SNAKE_HEAD;
	gridCells[snake.getBody().x][snake.getBody().y].objectID = ObjectID::SNAKE_BODY;
	gridCells[snake.getTail().x][snake.getTail().y].objectID = ObjectID::SNAKE_TAIL;
}

void SnakeGrid::detectKeyboard() {				//detect pressed keys and change snake's direction
	if (IM.IsKeyDown<'w'>())
		snake.setDirection(Snake::directions::up);
	if (IM.IsKeyDown<'s'>())
		snake.setDirection(Snake::directions::down);
	if (IM.IsKeyDown<'a'>())
		snake.setDirection(Snake::directions::left);
	if (IM.IsKeyDown<'d'>())
		snake.setDirection(Snake::directions::right);
}