#include "LevelDetails.hh"
#include "TimeManager.hh"
#include <iostream>

void levelDetails::startGame()
{
	level = 0;
	lives = 3;
	score = 0;
	food = 1;
	time = 0;
	snakeVel = getInitSnakeVel();
}

void levelDetails::resetLevel()
{
	// es reinicia el contador de la score? torna a com estava al principi d'aquell nivell?
	food = 1;
	time = 0;
	lives--;
}

void levelDetails::nextLevel()
{
	food = 1;
	time = 0;
	level++;
	std::cout << "level " << level << "\n";
}

bool levelDetails::isTimeOver()
{
	return time > getInitTimeToComplete();
}

bool levelDetails::isGameOver()
{
	if (lives <= 0) {
		return true;
	}
	return false;
}

bool levelDetails::isLevelCompleted()
{
	return food > (getInitFood()+foodIncrease()*level);
}


void levelDetails::appleEaten()
{
	score += food * 100;
	//snakeVel += score / 1000;	//updateTime
	food++;
}

void levelDetails::updateTimer()
{
	time += TM.GetDeltaTime();
}


levelDetails::levelDetails()
{

}

levelDetails::~levelDetails()
{
}