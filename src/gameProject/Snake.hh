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
	Snake(snakeCell newHead, directions movingDirection);
	~Snake();
	void Update();
	void growUp();							//when the snake eats an apple and grows up
	void setDirection(directions newDir);
	void reset();
	snakeCell getHead();							//returns the snake's head cell			------ (usar els metodes front() i back() del deque
	snakeCell getTail();							//returns the snake's tail cell (the last cell)
	snakeCell nextPosition();					//where the head it's going to be after moving
	//fer algun metode per obtenir un iterador de totes les caselles, o algo per obtenir totes les caselles
private:
	directions movDirection;				//the direction the snake is moving
	//snakeCell previousTail;						//tail's position before moving			-----no se si realment fa falta
	std::deque<snakeCell> cells;
	bool growing;
	snakeCell startingCell;
	directions startingDir;
};