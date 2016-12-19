#include "MenuScene.hh"
#include "GUI.hh"

MenuScene::MenuScene(void)
{
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };

}

MenuScene::~MenuScene()
{

}

void MenuScene::OnEntry(void)
{

}

void MenuScene::OnExit(void)
{

}

void MenuScene::Update(void)
{

}

void MenuScene::Draw(void)
{
	m_background.Draw(); // Render background

	GUI::DrawTextShaded<FontID::CANDY>("Play",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::CANDY>("Exit",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated

										//std::string &&msg, Transform &&transform, Color &&foregroundColor, Color &&backgroundColor

}