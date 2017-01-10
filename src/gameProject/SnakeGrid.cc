#pragma once
#include <ctime>
#include "SnakeGrid.hh"
#include "Snake.hh"
#include "InputManager.hh"
#include "TimeManager.hh"
#include "SnakeScene.hh"
#include "IOManager.hh"
#include "LevelDetails.hh"

#define updateTime 200
#define initLives 3

SnakeGrid::SnakeGrid(Sint32 ncellWidth, Sint32 ncellHeight) : snake({ 1,3 })
{
	srand(unsigned(time(nullptr)));						//in order to get random numbers
	cellWidth = ncellWidth;
	cellHeight = ncellHeight;

	timeToUpdate = updateTime;
	
}

SnakeGrid::~SnakeGrid()
{
	for (int row = 0; row < lvlDetails.getCells(); ++row) {
		delete[] gridCells[row];
	}
	delete[] gridCells;
}

void SnakeGrid::start(std::string difStr) {					//start game for the first time
	lvlDetails = IOManager::loadxml(difStr);
	lvlDetails.setInitValues(0, lvlDetails.getCells() + 2);	//add 2 rows / colms. for borders
	lvlDetails.startGame();
	gridCells = new Sprite*[lvlDetails.getCells()];						//create rows
	for (int i = 0; i < lvlDetails.getCells(); ++i) {
		gridCells[i] = new Sprite[lvlDetails.getCells()];				//create columns for every row
	}
	resetGrid();
}

void SnakeGrid::Update()
{
	lvlDetails.updateTimer();
	detectKeyboard();
	snakeTimer += TM.GetDeltaTime();
	if (snakeTimer > timeToUpdate)
	{
		snakeTimer = 0;
		snakeCell nextCell = snake.nextPosition();
		ObjectID cellID = gridCells[nextCell.x][nextCell.y].objectID;

		if (isInsideGrid(nextCell) && (cellID == ObjectID::EMPTY_SNAKE 
				|| cellID == ObjectID::SNAKE_APLE)) {		//only move snake if next position is empty or an apple
			if (cellID == ObjectID::SNAKE_APLE)						//if it's an apple: add score, place a new one, grow snake
				{
					lvlDetails.appleEaten();
					placeApple();
					snake.growUp();
				}
			if (lvlDetails.isLevelCompleted() || lvlDetails.isTimeOver()) {
				resetGrid();
				if(lvlDetails.isLevelCompleted())
					lvlDetails.nextLevel();

			}
			else {					//update snake's position in grid if everything was ok
				updateGrid();
			}
				
		}
		else {						//snake has crashed with a wall
			lvlDetails.resetLevel();
			resetGrid();
		}
	}
}

void SnakeGrid::Draw()
{
	for (int row = 0; row < lvlDetails.getCells(); ++row) {
		for (int col = 0; col < lvlDetails.getCells(); ++col) {
			gridCells[row][col].Draw();
		}
	}
}

void SnakeGrid::resetGrid()
{
	for (int row = 0; row < lvlDetails.getCells(); ++row) {				//initialize grid
		for (int col = 0; col < lvlDetails.getCells(); ++col) {
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
	snake = Snake({ 1,3 });
	placeSnake();
	placeApple();										//insert apple
	snakeTimer = 0;
	timeToUpdate = updateTime;
}

Snake SnakeGrid::getSnake()
{
	return snake;
}

bool SnakeGrid::isInsideGrid(snakeCell cell)		//returns true if given cell is inside the grid (without touching the borders)
{
	if (cell.x > 0 && cell.x < lvlDetails.getCells()-1 && cell.y > 0 && cell.y < lvlDetails.getCells() - 1) {
		return true;
	}
	return false;
}

void SnakeGrid::placeApple() {				//places apple in a random empty cell
	int randCol = 1+rand()%(lvlDetails.getCells()-2);
	int randRow = 1 + rand() % (lvlDetails.getCells()- 2);
	while (gridCells[randRow][randCol].objectID != ObjectID::EMPTY_SNAKE) {
		randCol = 1 + rand() % (lvlDetails.getCells()- 2);
		randRow = 1 + rand() % (lvlDetails.getCells()- 2);
	}
	gridCells[randRow][randCol].objectID = ObjectID::SNAKE_APLE;
	timeToUpdate -= 5;
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

bool SnakeGrid::gameEnded()
{
	return lvlDetails.isGameOver();
}

int SnakeGrid::currentScore()
{
	return lvlDetails.getScore();
}

int SnakeGrid::timeLeft()
{
	return int((lvlDetails.getInitTimeToComplete()-lvlDetails.getTime())/1000);
}

void SnakeGrid::updateGrid()
{
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

