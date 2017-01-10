#pragma once
#include <deque>
#include <SDL.h>

struct snakeCell
{
	Sint32 x;
	Sint32 y;
};

class Snake
{
public:
	enum class directions
	{
		up,
		down,
		left,
		right
	};
	Snake(snakeCell newHead);
	~Snake();
	void Update();
	void growUp();							//when the snake eats an apple and grows up
	void setDirection(directions newDir);

	snakeCell getHead();							//returns the snake's head cell			------ (usar els metodes front() i back() del deque
	snakeCell getBody();							//returns the snake's body (second cell)
	snakeCell getTail();							//returns the snake's tail cell (the last cell)
	snakeCell nextPosition();						//where the head it's going to be after moving
	snakeCell nextPosition(directions testingDir);
	snakeCell prevTail();							//where the head it's going to be after moving
	Snake::directions getDirection();

	bool hasMoved();
	int getSize();

private:
	directions movDirection;				//the direction the snake is moving
	snakeCell previousTail;					//tail's position before moving			-----no se si realment fa falta
	snakeCell startingCell;
	directions startingDir;
	std::deque<snakeCell> cells;
	bool growing;
};