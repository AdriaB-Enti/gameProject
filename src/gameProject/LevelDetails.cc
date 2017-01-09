#include "LevelDetails.hh"
#include "TimeManager.hh"

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


void levelDetails::appleEaten()
{
	score += food * 100;
	snakeVel += score / 1000;	//mirar bé...
	food++;
}

void levelDetails::updateTimer()
{
	time += TM.GetDeltaTime();
}


void levelDetails::testing()	//BORRAR
{
	
}

levelDetails::levelDetails()
{

}

levelDetails::~levelDetails()
{
}