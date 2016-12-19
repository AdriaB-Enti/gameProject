
#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : const int {
	EMPTY_SNAKE,SNAKE_APLE, SNAKE_HEAD, SNAKE_BODY, SNAKE_TAIL, SNAKE_WALL, CANDY_MAX, // Candies IDs
	CELL_EMPTY, // Cell IDs
	BG_00,  // Background IDs
	BG_01 //Background Menu
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator >> (std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int {
	ARIAL,
	CANDY,
	FACTORY,
	MAX
};