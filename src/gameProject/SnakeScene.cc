#pragma once
#include "SnakeScene.hh"
#include "MenuScene.hh"

difficulty SnakeScene::selectedDif = difficulty::easy;

SnakeScene::SnakeScene(void) {
}

SnakeScene::~SnakeScene()
{
}

void SnakeScene::OnEntry(void)
{
}

void SnakeScene::OnExit(void)
{
}

void SnakeScene::Update(void)
{
}

void SnakeScene::Draw(void)
{
}

void SnakeScene::setDifficulty(const difficulty d)
{
	SnakeScene::selectedDif = d;
}


