#pragma once
#include "Snake.hh"


Snake::Snake(snakeCell newHead)
{
	cells.push_front(newHead);			//head
	movDirection = directions::down;	//snake starts moving downwards by default
	newHead.y--;
	cells.push_back(newHead);			//body
	newHead.y--;
	cells.push_back(newHead);			//tail
	growing = false;
	previousTail = getTail();
}

Snake::~Snake()
{

}

void Snake::Update() {
	previousTail = getTail();
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
	//check if we are chosing a valid direction
	//if snake would move to its body, direction isn't change
	snakeCell nextPos = nextPosition(newDir);
	if (nextPos.x != getBody().x || nextPos.y != getBody().y) {
		movDirection = newDir;
	}
}

snakeCell Snake::getHead() {
	return cells.front();
}

snakeCell Snake::getBody()
{
	return cells.at(1);
}

snakeCell Snake::getTail() {
	return cells.back();
}

snakeCell Snake::nextPosition() {
	return nextPosition(movDirection);
}

snakeCell Snake::nextPosition(directions testingDir) {
	snakeCell nextPos = getHead();
	switch (testingDir)
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

snakeCell Snake::prevTail()
{
	return previousTail;
}

Snake::directions Snake::getDirection()
{
	return movDirection;
}

bool Snake::hasMoved()
{
	return (previousTail.x != getTail().x || previousTail.y != getTail().y);
}

int Snake::getSize()			//snake size (including head and tail cells)
{
	return cells.size();
}
