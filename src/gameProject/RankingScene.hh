#pragma once
#include "Scene.hh"
#include "Button.h"
#include "Sprite.hh"
#include "Score.hh"
#include "IOManager.hh"

/*
Scene to show all highscores
*/
class  RankingScene : public Scene
{
public:
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	static int scoreToSave;
private:
	bool askingName;			//whether we are selecting the difficulty or not
	std::string playerName;
	Button menu, exit;
	std::list<Score> scoreList;
};

