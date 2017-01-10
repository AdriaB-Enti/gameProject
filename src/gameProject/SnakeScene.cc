#pragma once
#include "SnakeScene.hh"
#include "MenuScene.hh"
#include "SceneManager.hh"

#define timeBarWidth 200

difficulty SnakeScene::selectedDif = difficulty::easy;

SnakeScene::SnakeScene(void):snakegrid(20, 20){
	timeBar = { { int(W.GetWidth() *.75f), int(W.GetHeight()*.7f), timeBarWidth, 40 },
		ObjectID::SNAKE_BAR, 0 };
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
	snakegrid.resetGrid();

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

	timeBar.transform.w = timeBarWidth * snakegrid.timeLeft();	//update the time bar lenght 
}

void SnakeScene::Draw(void)
{
	snakegrid.Draw();

	GUI::DrawTextSolid<FontID::FACTORY>("Score:",
	{ int(W.GetWidth() *.8f), int(W.GetHeight()*.25f), 1, 1 },
	{ 50, 200,0 });
	GUI::DrawTextSolid<FontID::FACTORY>(std::to_string(snakegrid.currentScore()),
	{ int(W.GetWidth() *.85f), int(W.GetHeight()*.35f), 1, 1 },
	{ 50, 200,0 });
	GUI::DrawTextSolid<FontID::ARIAL>("Time:",
	{ int(W.GetWidth() *.8f), int(W.GetHeight()*.66f), 1, 1 },
	{ 250, 50,0 });

	timeBar.Draw();

}

void SnakeScene::setDifficulty(const difficulty d)
{
	SnakeScene::selectedDif = d;
}

difficulty SnakeScene::getDifficulty()
{
	return selectedDif;
}
