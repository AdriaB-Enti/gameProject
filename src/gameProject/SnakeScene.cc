#pragma once
#include "SnakeScene.hh"
#include "MenuScene.hh"

difficulty SnakeScene::selectedDif = difficulty::easy;

SnakeScene::SnakeScene(void):snakegrid(20, 20, 20, 20){

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
	snakegrid.Update();
}

void SnakeScene::Draw(void)
{
	snakegrid.Draw();
}

void SnakeScene::setDifficulty(const difficulty d)
{
	SnakeScene::selectedDif = d;
}