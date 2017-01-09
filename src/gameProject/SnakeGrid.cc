#pragma once
#include <ctime>
#include "SnakeGrid.hh"
#include "Snake.hh"
#include "InputManager.hh"
#include "TimeManager.hh"
#include "SnakeScene.hh"
#include "IOManager.hh"

#define updateTime 200
#define initLives 3

SnakeGrid::SnakeGrid(Sint32 ncellWidth, Sint32 ncellHeight) : snake({ 1,3 })
{
	timeToUpdate = updateTime;

	if (SnakeScene::getDifficulty() == difficulty::easy) {
		rows = 10;
		columns = 10;
	}
	//IOManager::xmlParameters parameters = IOManager::loadxml("Easy");

	rows +=2;										//2 extra cells for borders on left and right
	columns +=2;									//same for columns
	cellWidth = ncellWidth;
	cellHeight = ncellHeight;
	//creating the grid:
	gridCells = new Sprite*[rows];						//create rows
	for (int i = 0; i < rows; ++i) {
		gridCells[i] = new Sprite[columns];				//create columns for every row
	}

	appleScore = 100;
	lives = initLives;
}

SnakeGrid::~SnakeGrid()
{
	for (int row = 0; row < rows; ++row) {
		delete[] gridCells[row];
	}
	delete[] gridCells;
}

void SnakeGrid::start(std::string difStr) {
	IOManager::xmlParameters parameters = IOManager::loadxml(difStr);
	rows = parameters.cells+2;										//2 extra cells for borders on left and right
	columns = parameters.cells+2;									//same for columns
	timeToComplete = parameters.timeToComplete;
	//velocidad
	initFood = parameters.initFood;
	foodIncrease = parameters.foodIncrease;
	//creating the grid:
	gridCells = new Sprite*[rows];						//create rows
	for (int i = 0; i < rows; ++i) {
		gridCells[i] = new Sprite[columns];				//create columns for every row
	}
}

void SnakeGrid::Update()
{
	detectKeyboard();
	timer += TM.GetDeltaTime();
	if (timer > timeToUpdate)
	{
		timer = 0;
		snakeCell nextCell = snake.nextPosition();
		ObjectID cellID = gridCells[nextCell.x][nextCell.y].objectID;

		if (isInsideGrid(nextCell) && (cellID == ObjectID::EMPTY_SNAKE 
				|| cellID == ObjectID::SNAKE_APLE)) {		//only move snake if next position is empty or an apple
			if (cellID == ObjectID::SNAKE_APLE)						//if it's an apple: add score, place a new one, grow snake
				{
					score += appleScore;
					placeApple();
					snake.growUp();
				}
				gridCells[snake.getHead().x][snake.getHead().y].objectID = ObjectID::SNAKE_BODY;
				snake.Update();
				gridCells[snake.getHead().x][snake.getHead().y].objectID = ObjectID::SNAKE_HEAD;

				switch (snake.getDirection())
				{
				case Snake::directions::down:
					gridCells[snake.getHead().x][snake.getHead().y].angle = 180;
					break;
				case Snake::directions::up:
					break;
				case Snake::directions::left:
					gridCells[snake.getHead().x][snake.getHead().y].angle = 270;
					break;
				case Snake::directions::right:
					gridCells[snake.getHead().x][snake.getHead().y].angle = 90;
					break;
				default:
					break;
				}

				gridCells[snake.getTail().x][snake.getTail().y].objectID = ObjectID::SNAKE_TAIL;
				if (snake.hasMoved()) {						//if snake has moved the tail, clear tail cell
					gridCells[snake.prevTail().x][snake.prevTail().y].objectID = ObjectID::EMPTY_SNAKE;
					gridCells[snake.prevTail().x][snake.prevTail().y].angle = 0;
				}
			
		}
		else {
			reset();
		}
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
	for (int row = 0; row < rows; ++row) {				//initialize grid
		for (int col = 0; col < columns; ++col) {
			gridCells[row][col].transform = { cellWidth / 2 + cellWidth*row,
				cellHeight / 2 + cellHeight*col, cellWidth, cellHeight };	//x, y, w, h
			if (isInsideGrid({col,row})) {
				gridCells[row][col].objectID = ObjectID::EMPTY_SNAKE;
			}
			else {
				gridCells[row][col].objectID = ObjectID::SNAKE_WALL;
			}
			gridCells[row][col].angle = 0;
		}
	}
	srand(unsigned(time(nullptr)));						//in order to get random numbers
	snake = Snake({ 1,3 });
	placeSnake();
	placeApple();										//insert apple
	timer = 0;
	score = 0;
	timeToUpdate = updateTime;
}

Snake SnakeGrid::getSnake()
{
	return snake;
}

bool SnakeGrid::isInsideGrid(snakeCell cell)		//returns true if given cell is inside the grid (without touching the borders)
{
	if (cell.x > 0 && cell.x < rows-1 && cell.y > 0 && cell.y < columns - 1) {
		return true;
	}
	return false;
}

void SnakeGrid::placeApple() {				//places apple in a random empty cell
	int randCol = 1+rand()%(columns-2);
	int randRow = 1 + rand() % (rows - 2);
	while (gridCells[randRow][randCol].objectID != ObjectID::EMPTY_SNAKE) {
		randCol = 1 + rand() % (columns - 2);
		randRow = 1 + rand() % (rows - 2);
	}
	gridCells[randRow][randCol].objectID = ObjectID::SNAKE_APLE;
	timeToUpdate -= 3;
}

void SnakeGrid::placeSnake()
{
	gridCells[snake.getHead().x][snake.getHead().y].objectID = ObjectID::SNAKE_HEAD;
	gridCells[snake.getHead().x][snake.getHead().y].angle = 180;
	gridCells[snake.getBody().x][snake.getBody().y].objectID = ObjectID::SNAKE_BODY;
	gridCells[snake.getBody().x][snake.getBody().y].angle = 180;
	gridCells[snake.getTail().x][snake.getTail().y].objectID = ObjectID::SNAKE_TAIL;
	gridCells[snake.getTail().x][snake.getTail().y].angle = 180;

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

