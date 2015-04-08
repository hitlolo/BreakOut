#include "GameScene.h"


GameScene* GameScene::create(int level)
{
	GameScene * ret = new (std::nothrow) GameScene();
	if (ret && ret->init(level))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameScene::init(int level)
{
	if (!Scene::init())
	{
		return false;
	}

	startGameByLevel(level);
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
