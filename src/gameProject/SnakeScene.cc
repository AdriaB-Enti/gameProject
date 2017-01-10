#pragma once
#include "SnakeScene.hh"
#include "MenuScene.hh"
#include "SceneManager.hh"
#include "InputManager.hh"

#define timeBarWidth 200

difficulty SnakeScene::selectedDif = difficulty::easy;

SnakeScene::SnakeScene(void):snakegrid(20, 20){
	timeBar = { { int(W.GetWidth() *.74f), int(W.GetHeight()*.7f), timeBarWidth, 40 },
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

	timeBar.transform.w = int(timeBarWidth * snakegrid.timeLeft());	//update the time bar lenght 
}

void SnakeScene::Draw(void)
{
	snakegrid.Draw();

	GUI::DrawTextSolid<FontID::FACTORY>("Score:",
	{ int(W.GetWidth() *.8f), int(W.GetHeight()*.2f), 1, 1 },
	{ 50, 200,0 });
	GUI::DrawTextSolid<FontID::FACTORY>(std::to_string(snakegrid.currentScore()),
	{ int(W.GetWidth() *.85f), int(W.GetHeight()*.3f), 1, 1 },
	{ 50, 200,0 });
	GUI::DrawTextSolid<FontID::ARIAL>("Lives: "+ std::to_string(snakegrid.currentLives()),
	{ int(W.GetWidth() *.8f), int(W.GetHeight()*.48f), 1, 1 },
	{ 50, 200,0 });
	GUI::DrawTextSolid<FontID::ARIAL>("Time:",
	{ int(W.GetWidth() *.79f), int(W.GetHeight()*.66f), 1, 1 },
	{ 50, 200,0 });

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
