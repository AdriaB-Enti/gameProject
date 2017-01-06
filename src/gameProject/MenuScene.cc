#pragma once
#include "MenuScene.hh"
#include "GUI.hh"
#include "SceneManager.hh"
#include "SnakeScene.hh"

MenuScene::MenuScene(void)
{
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };

	play.init("Play", { W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 });
	exit.init("Exit", { W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 });

	easy.init("Easy", { W.GetWidth()/8, W.GetHeight()>>1, 1, 1 });
	medium.init("Medium", { 4*W.GetWidth()/8, W.GetHeight()>>1, 1, 1 });
	hard.init("Hard", { 7*W.GetWidth()/8, W.GetHeight()>>1, 1, 1 });
	std::cout << "Menu es construeix\n";
}

MenuScene::~MenuScene()
{
}

void MenuScene::OnEntry(void)
{
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
			SM.SetCurScene<SnakeScene>(); //load snake scene
			std::cout << "Loading..." << std::endl;
		}
		if (medium.isInside(mouseCoords.x, mouseCoords.y)) {
			SM.SetCurScene<SnakeScene>(); //load snake scene
			std::cout << "Loading..." << std::endl;
		}
		if (hard.isInside(mouseCoords.x, mouseCoords.y)) {
			SM.SetCurScene<SnakeScene>();	//load snake scene
			std::cout << "Loading..." << std::endl;
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
	play.isActive = true;
	exit.isActive = true;
	easy.isActive = false;
	medium.isActive = false;
	hard.isActive = false;
}

//only "Easy", "Medium" and "Hard" buttons are visible
void MenuScene::setDifButtons()
{
	play.isActive = false;
	exit.isActive = false;
	easy.isActive = true;
	medium.isActive = true;
	hard.isActive = true;
}
