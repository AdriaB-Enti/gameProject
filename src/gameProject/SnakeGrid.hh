#pragma once
#include "Sprite.hh"
#include "Snake.hh"


class SnakeGrid
{
public:
	SnakeGrid(Sint32 nrows, Sint32 ncols, Sint32 cellWidth, Sint32 cellHeight);
	~SnakeGrid();
	void Update();
	void Draw();
	void reset();
	Snake getSnake();
	void placeApple();
	void placeSnake();
	void detectKeyboard();
private:
	bool isInsideGrid(snakeCell cell);	//for checking if a cell is outside the grid
	Sint32 rows, columns;			//number of cells in a row / column
	Sint32 cellWidth, cellHeight;
	//no sé si per la Grid lo millor seria fer un doble punter com el Jordi, o una llista, o un diccionari (posicio-Sprite)...
	Sprite **gridCells;
	//estructura da dades per les pomes?
	//estructura de dades per els obstacles?
	Snake snake;
};
