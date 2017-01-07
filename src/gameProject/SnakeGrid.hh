#pragma once
#include "Sprite.hh"
#include "Snake.hh"


class SnakeGrid
{
public:
	SnakeGrid(Sint32 nrows, Sint32 ncols);
	~SnakeGrid();
	void Update();
	void Draw();
	void reset();
	Snake getSnake();
private:
	bool isOutsideGrid(Cell cell);	//for checking if a cell is outside the grid
	Sint32 rows, columns;			//number of cells in a row / column
	//no sé si per la Grid lo millor seria fer un doble punter com el Jordi, o una llista, o un diccionari (posicio-Sprite)...
	//estructura da dades per les pomes?
	//estructura de dades per els obstacles?
	Snake snake;
};
