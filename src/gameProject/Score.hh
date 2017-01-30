#pragma once
#include <string>

struct Score
{
	std::string name;
	int points;
	bool operator<(Score score2) {
		return points < score2.points;
	}
};