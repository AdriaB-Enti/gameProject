#pragma once
#include "MenuScene.hh"
#include "GUI.hh"
#include "SceneManager.hh"
#include "SnakeScene.hh"
#include "InputManager.hh"

MenuScene::MenuScene(void)
{
	selectingDif = false;
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01, 0};
	play.init("Play", { W.GetWidth() >> 1, int(W.GetHeight()*.15f), 1, 1 });
	exit.init("Exit", { W.GetWidth() >> 1, int(W.GetHeight()*.75f), 1, 1 });

	easy.init("Easy", { W.GetWidth()/8, W.GetHeight()>>1, 1, 1 });
	medium.init("Medium", { 4*W.GetWidth()/8, W.GetHeight()>>1, 1, 1 });
	hard.init("Hard", { 7*W.GetWidth()/8, W.GetHeight()>>1, 1, 1 });
}

MenuScene::~MenuScene()
{
}

void MenuScene::OnEntry(void)
{
	selectingDif = false;
	setInitButtons();
}

void MenuScene::OnExit(void)
{

}

void MenuScene::Update(void)
{
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		MouseCoords mouseCoords = IM.GetMouseCoords();
		if (play.isInside(mouseCoords.x, mouseCoords.y)) {
			setDifButtons();
		}
		if (exit.isInside(mouseCoords.x, mouseCoords.y)) {
			std::cout << "Exit..." << std::endl;
			SetState<SceneState::EXIT>();
		}
		if (easy.isInside(mouseCoords.x, mouseCoords.y)) {
			SnakeScene::setDifficulty(difficulty::easy);
			SM.SetCurScene<SnakeScene>(); //load snake scene
			std::cout << "Loading Easy..." << std::endl;
		}
		if (medium.isInside(mouseCoords.x, mouseCoords.y)) {
			SnakeScene::setDifficulty(difficulty::medium);
			SM.SetCurScene<SnakeScene>(); //load snake scene
			std::cout << "Loading Medium..." << std::endl;
		}
		if (hard.isInside(mouseCoords.x, mouseCoords.y)) {
			SnakeScene::setDifficulty(difficulty::hard);
			SM.SetCurScene<SnakeScene>();	//load snake scene
			std::cout << "Loading Hard..." << std::endl;
		}
	}
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {	//when pressing scape, Play and exit are shown
		if (!selectingDif)
		{
			std::cout << "Exit" << std::endl;
			SetState<SceneState::EXIT>();
		}
		else {
			setInitButtons();
		}
	}
}

void MenuScene::Draw(void)
{
	m_background.Draw(); // Render background

	play.Draw();
	exit.Draw();

	easy.Draw();
	medium.Draw();
	hard.Draw();

}

//only "Play" and "Exit" buttons are visible
void MenuScene::setInitButtons()
{
	selectingDif = false;
	play.isActive = true;
	exit.isActive = true;
	easy.isActive = false;
	medium.isActive = false;
	hard.isActive = false;
}

//only "Easy", "Medium" and "Hard" buttons are visible
void MenuScene::setDifButtons()
{
	selectingDif = true;
	play.isActive = false;
	exit.isActive = false;
	easy.isActive = true;
	medium.isActive = true;
	hard.isActive = true;
}
