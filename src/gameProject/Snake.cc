#pragma once
#include "Snake.hh"


Snake::Snake(Cell newHead)
{
	cells.push_front(newHead);
	//decidir que fer amb la resta de caselles (tail i demés possibles caselles)...
	movDirection = directions::right;
}

Snake::~Snake()
{
}

void Snake::Update() {					//moure la serp
	cells.push_front(nextPosition());	//move head 1 cell
	cells.pop_back();					//remove tail
}

Cell Snake::getHead() {
	return cells.front();
}

Cell Snake::getTail() {
	return cells.back();
}

Cell Snake::nextPosition() {
	Cell nextPos = getHead();

	switch (movDirection)
	{
	case Snake::directions::up:
		nextPos.y++;
		break;
	case Snake::directions::down:
		nextPos.y--;
		break;
	case Snake::directions::left:
		nextPos.x++;
		break;
	case Snake::directions::right:
		nextPos.x--;
		break;
	default:
		break;
	}

	return nextPos;
}