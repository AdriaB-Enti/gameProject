
#pragma once
#include "Scene.hh"
#include "SnakeGrid.hh"

enum class difficulty
{
	easy,
	medium,
	hard
};

// gameplay scene
class SnakeScene : public Scene {
public:
	explicit SnakeScene();
	~SnakeScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static void setDifficulty(const difficulty d);
	static difficulty getDifficulty();

private:
	static difficulty selectedDif;					//selected difficulty
	SnakeGrid snakegrid;
	Sprite timeBar;
};