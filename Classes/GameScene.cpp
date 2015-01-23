#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	startGameByLevel(0);
	return true;
}

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::startGameByLevel(int level)
{
	auto gameWorld = GameWorld::create(level);
	this->addChild(gameWorld);

}

void GameScene::initLevelDataTMX(int level)
{

}