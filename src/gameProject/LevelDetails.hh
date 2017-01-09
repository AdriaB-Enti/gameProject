#pragma once
#include <iostream>

class levelDetails
{
public:
	void startGame();
	void resetLevel();
	void nextLevel();

	inline void setInitValues(int pos, int value) {initValues[pos] = value;};	//set value in initValues array pos

	inline int getCells() {return initValues[0];};
	inline int getInitTimeToComplete() {return initValues[1];};
	inline int getInitSnakeVel() { return initValues[2]; };
	inline int getInitFood() { return initValues[3]; };
	inline int foodIncrease() { return initValues[4]; };

	inline int getlives() { return lives; };
	inline int getScore() { return score; };

	bool isTimeOver();				//check if available time has run out
	bool isGameOver();
	void appleEaten();
	void updateTimer();

	void testing();

	levelDetails();
	~levelDetails();

private:
	int level, lives, score, food, time, snakeVel;
	int initValues[5];				//cells, timeToComplete, snakeVel, initFood, foodIncrease
};