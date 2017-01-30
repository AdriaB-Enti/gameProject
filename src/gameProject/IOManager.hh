#pragma once
#include "LevelDetails.hh"
#include <iostream>
#include <list>
#include "Score.hh"


namespace IOManager {
	
	levelDetails loadxml(std::string difficulty);
	void readScores(std::list<Score> &scoreList);
	void saveScores(std::list<Score> &scoreList);
}