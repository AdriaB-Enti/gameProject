#pragma once
#include "RankingScene.hh"
#include "GUI.hh"
#include "SceneManager.hh"
#include "MenuScene.hh"
#include "InputManager.hh"

int RankingScene::scoreToSave = 0;


RankingScene::RankingScene(void)
{
	askingName = true;
	menu.init("Return to menu", { int(W.GetWidth()*.2f), int(W.GetHeight()*.84f), 1, 1 });
	exit.init("Exit game", { int(W.GetWidth()*.8f), int(W.GetHeight()*.84f), 1, 1 });
}

RankingScene::~RankingScene()
{
}

void RankingScene::OnEntry(void)
{
	playerName = "";
	askingName = true;
	setInitButtons();
	
	std::cout << "score is " << scoreToSave << std::endl;	//BORRAR

	IOManager::readScores(scoreList);
	//IOManager::saveScores(scoreList);
}

void RankingScene::OnExit(void)
{

}

void RankingScene::Update(void)
{
	if (askingName)
	{
		if (IM.IsKeyDown<KEY_BUTTON_BACKSPACE>() && playerName.length() > 0) {
			playerName.pop_back();
		}

		if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {				//submit score
			if (playerName.length() > 0)
			{
				Score newScore;
				newScore.name = playerName;
				newScore.points = scoreToSave;
				scoreList.push_back(newScore);
				scoreList.sort();

				if (scoreList.size() > 10)
				{
					scoreList.pop_front();					//if there are more than 10 scores, delete the smallest
				}
				//IOManager::saveScores(scoreList);			//save File
				askingName = false;
			}
			else
			{
				std::cout << "Player name must be at least 1 character long\n";
			}
		}

		if (playerName.length() < 10)							//10 chars maximum
		{
			Sint32 keyDown = IM.whatKeyIsDown();				//check if player has pressed any key
			if (keyDown != NULL)
			{
				playerName += (char)keyDown;					//if so, update playerName string
			}
		}
	}
	

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		MouseCoords mouseCoords = IM.GetMouseCoords();
		if (menu.isInside(mouseCoords.x, mouseCoords.y)) {
			SM.SceneManager::SetCurScene<MenuScene>();
		}
		if (exit.isInside(mouseCoords.x, mouseCoords.y)) {
			SetState<SceneState::EXIT>();
		}
	}
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {				//pressing Escape quits the game
		SetState<SceneState::EXIT>();
	}
}

void RankingScene::Draw(void)
{
	drawScores();

	GUI::DrawTextSolid<FontID::ARIAL>(askingName ? "Enter your name: " + playerName : "Scores updated!",
	{ W.GetWidth()>>1, int(W.GetHeight()*.74f), 1, 1 },
	{ 50, 200,0 });

	menu.Draw();
	exit.Draw();
}

//only "Play" and "Exit" buttons are visible
void RankingScene::setInitButtons()
{
	menu.isActive = true;
	exit.isActive = true;
}

//only "Easy", "Medium" and "Hard" buttons are visible
void RankingScene::setDifButtons()
{
	menu.isActive = false;
	exit.isActive = false;
}

void RankingScene::drawScores()
{
	float newPosition = 0.06f;
	for (auto it = scoreList.rbegin(); it != scoreList.rend(); it++)				//iterate the list backwards, we want to show higher scores first, then the lower ones
	{
		GUI::DrawTextSolid<FontID::ARIAL>(it->name+" "+ std::to_string(it->points),
		{ W.GetWidth() >> 1, int(W.GetHeight()*newPosition), 1, 1 },
		{ 50, 200,0 });
		newPosition += .06f;
	}
}
