#include "MenuScene.hh"
#include "GUI.hh"
Transform tr;


MenuScene::MenuScene(void)
{
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };

	play.init("Play", { W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 });
	exit.init("Exit", { W.GetWidth() >> 1, int(W.GetHeight()*.8f), 1, 1 });
}

MenuScene::~MenuScene()
{

}

void MenuScene::OnEntry(void)
{
	std::cout << "ENTRY";
}

void MenuScene::OnExit(void)
{
	std::cout << "EXIT SCENE";
}

void MenuScene::Update(void)
{
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		MouseCoords mouseCoords = IM.GetMouseCoords();
		if (play.isInside(mouseCoords.x, mouseCoords.y)) {
			//SM.SetCurScene<------>();//carregar pantalla?
			std::cout << "Loading..." << std::endl;
		}
		if (exit.isInside(mouseCoords.x, mouseCoords.y)) {
			std::cout << "Exit..." << std::endl;
			SetState<SceneState::EXIT>();
		}
	}

}

void MenuScene::Draw(void)
{
	m_background.Draw(); // Render background

	play.Draw();
	exit.Draw();

}