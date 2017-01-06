
#pragma once
#include "Scene.hh"

// gameplay scene
class SnakeScene : public Scene {
public:
	explicit SnakeScene();
	~SnakeScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:

};