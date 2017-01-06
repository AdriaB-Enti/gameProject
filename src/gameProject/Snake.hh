#pragma once
#include "SnakeGrid.hh"


struct Cell
{
	Sint32 x;
	Sint32 y;
};

class Snake
{
public:
	Snake();
	~Snake();
	void Update();
	void growUp();							//when the snake eats an apple and grows up
	enum class directions
	{
		up,
		down,
		left,
		right
	};
	void setDirection(directions newDir);
	void reset();
	Cell head();							//returns the snake's head cell
	Cell tail();							//returns the snake's tail cell (the last cell)
	Cell nextPosition();					//where the head it's going to be after moving
private:
	directions movDirection;				//the direction the snake is moving
	//segurament un dequeue de Cell's per tota la serp
	Cell previousTail;						//tail's position before moving
};

Snake::Snake()
{
}

Snake::~Snake()
{
}