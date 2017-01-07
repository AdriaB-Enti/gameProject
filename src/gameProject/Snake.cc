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

//auto Snake::getIterator()		//for iterating all snake cells
//{
//	return cells.begin;
//}

int Snake::getSize()			//snake size (including head and tail cells)
{
	return cells.size();
}
