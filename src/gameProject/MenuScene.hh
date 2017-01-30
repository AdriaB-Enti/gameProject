
#pragma once
#include "Scene.hh"
#include "Button.h"
#include "Sprite.hh"

class  MenuScene : public Scene
{
public:
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void setInitButtons();
	void setDifButtons();
private:
	bool selectingDif;			//wheter we are selecting the difficulty or not
	Button play, exit;
	Button easy, medium, hard;
	Sprite m_background;
};

