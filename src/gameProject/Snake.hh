#pragma once
#include <deque>
#include <SDL.h>

struct Cell
{
	Sint32 x;
	Sint32 y;
};

class Snake
{
public:
	Snake(Cell newHead);
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
	Cell getHead();							//returns the snake's head cell			------ (usar els metodes front() i back() del deque
	Cell getTail();							//returns the snake's tail cell (the last cell)
	Cell nextPosition();					//where the head it's going to be after moving
	//fer algun metode per obtenir un iterador de totes les caselles, o algo per obtenir totes les caselles
private:
	directions movDirection;				//the direction the snake is moving
	//segurament un dequeue de Cell's per tota la serp
	Cell previousTail;						//tail's position before moving			-----no se si realment fa falta
	std::deque<Cell> cells;
};