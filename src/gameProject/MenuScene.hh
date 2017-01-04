
#pragma once

#include "Grid.hh"
#include "Scene.hh"
#include "Button.h"

class  MenuScene : public Scene
{
public:
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

private:
	Button play, exit;
	Sprite m_background;

};

