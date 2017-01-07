#pragma once
#include "Snake.hh"


Snake::Snake(snakeCell newHead)
{
	cells.push_front(newHead);
	//decidir que fer amb la resta de caselles (tail i demés possibles caselles)...
	movDirection = directions::right;
	growing = false;

}

Snake::Snake(snakeCell newHead, directions movingDirection)
{
	startingCell = newHead;
	startingDir = movingDirection;
	cells.push_front(newHead);
	//decidir que fer amb la resta de caselles (tail i demés possibles caselles)...
	movDirection = directions::right;
	growing = false;
}

Snake::~Snake()
{

}

void Snake::Update() {
	cells.push_front(nextPosition());		//move snake's head one position (1 cell)
	if (!growing) {
		cells.pop_back();					//remove tail
	}
	else {
		growing = false;					//not removing the tail makes the snake grow 1 cell
	}
}

void Snake::growUp()
{
	growing = true;
}

void Snake::setDirection(directions newDir)
{
	movDirection = newDir;
}

void Snake::reset()
{
}

snakeCell Snake::getHead() {
	return cells.front();
}

snakeCell Snake::getTail() {
	return cells.back();
}

snakeCell Snake::nextPosition() {
	snakeCell nextPos = getHead();

	switch (movDirection)
	{
	case Snake::directions::up:
		nextPos.y--;
		break;
	case Snake::directions::down:
		nextPos.y++;
		break;
	case Snake::directions::left:
		nextPos.x--;
		break;
	case Snake::directions::right:
		nextPos.x++;
		break;
	default:
		break;
	}

	return nextPos;
}