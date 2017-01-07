#include "SnakeGrid.hh"



SnakeGrid::SnakeGrid(Sint32 nrows, Sint32 ncols) : snake({ 1,1 })
{
	rows = nrows;
	columns = ncols;

	//crear grid
}

SnakeGrid::~SnakeGrid()
{
}

void SnakeGrid::Update()
{
}

void SnakeGrid::Draw()
{
}

void SnakeGrid::reset()
{
}

Snake SnakeGrid::getSnake()
{
	return snake;
}

bool SnakeGrid::isOutsideGrid(Cell cell)
{
	//if()... return true
	return false;
}
