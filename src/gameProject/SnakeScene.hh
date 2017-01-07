
#pragma once
#include "Scene.hh"

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
	static void setDifficulty(const difficulty d) /*{selectedDif = d;}*/;
private:
	//playing state -> joc en marxa o joc parat (amb el menu in-game)
	static difficulty selectedDif;					//selected difficulty
	
};