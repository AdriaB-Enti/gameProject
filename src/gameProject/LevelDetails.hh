#pragma once
/*
This class will be used to store all parameters needed in every level and has all the functionalty necessary
It's the class used to store level configuration readen from the xml
*/
class levelDetails
{
public:
	inline void setInitValues(int pos, int value) {initValues[pos] = value;};	//set value in initValues array pos

	inline int getCells() {return initValues[0];};
	inline int getInitTimeToComplete() {return initValues[1];};
	inline int getInitSnakeVel() { return initValues[2]; };
	inline int getInitFood() { return initValues[3]; };
	inline int foodIncrease() { return initValues[4]; };

	inline int getlives() { return lives; };
	inline int getScore() { return score; };
	inline float getTime() { return time; };

	bool isTimeOver();				//check if available time has run out
	bool isGameOver();
	bool isLevelCompleted();
	void appleEaten();
	void updateTimer();

	void startGame();
	void resetLevel();
	void nextLevel();

	levelDetails();
	~levelDetails();

private:
	int level, lives, score, food, snakeVel;
	float time;
	int initValues[5];				//cells, timeToComplete, snakeVel, initFood, foodIncrease
};