#pragma once
#include "SnakeScene.hh"
#include "MenuScene.hh"
#include "SceneManager.hh"
//#include "IOManager.hh"

difficulty SnakeScene::selectedDif = difficulty::easy;

SnakeScene::SnakeScene(void):snakegrid(20, 20){

}

SnakeScene::~SnakeScene()
{
}

void SnakeScene::OnEntry(void)
{
	std::string difString ="";
	switch (selectedDif)
	{
	case difficulty::easy: difString = "Easy";
		break;
	case difficulty::medium: difString = "Medium";
		break;
	case difficulty::hard: difString = "Hard";
		break;
	}
	//snakegrid.start(difString);
	//IOManager::loadxml(difString);

	snakegrid.reset();

}

void SnakeScene::OnExit(void)
{
}

void SnakeScene::Update(void)
{
	snakegrid.Update();

	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {	//when pressing scape, we go back to the menu
		SM.SetCurScene<MenuScene>();
	}
}

void SnakeScene::Draw(void)
{
	snakegrid.Draw();
}

void SnakeScene::setDifficulty(const difficulty d)
{
	SnakeScene::selectedDif = d;
}

difficulty SnakeScene::getDifficulty()
{
	return selectedDif;
}
