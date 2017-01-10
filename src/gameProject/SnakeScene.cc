#pragma once
#include "SnakeScene.hh"
#include "MenuScene.hh"
#include "SceneManager.hh"

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
	snakegrid.start(difString);
	snakegrid.resetGrid();			//cal?

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

	if (snakegrid.gameEnded())					//if game ends, go to Menu scene
	{
		SM.SetCurScene<MenuScene>();
	}
}

void SnakeScene::Draw(void)
{
	snakegrid.Draw();
	GUI::DrawTextSolid<FontID::FACTORY>(std::to_string(snakegrid.currentScore()),
	{ int(W.GetWidth() *.85f), int(W.GetHeight()*.1f), 1, 1 },
	{ 50, 200,0 });
	
	GUI::DrawTextSolid<FontID::FACTORY>(std::to_string(snakegrid.timeLeft()),
	{ int(W.GetWidth() *.85f), int(W.GetHeight()*.5f), 1, 1 },
	{ 250, 50,0 });
}

void SnakeScene::setDifficulty(const difficulty d)
{
	SnakeScene::selectedDif = d;
}

difficulty SnakeScene::getDifficulty()
{
	return selectedDif;
}
