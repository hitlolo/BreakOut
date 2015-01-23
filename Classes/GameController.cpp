#include "GameController.h"

GameController* GameController::_controller = nullptr;

GameController* GameController::getInstance()
{
	if (_controller == nullptr)
	{
		_controller = new GameController();
		return _controller;
	}
	else
		return _controller;
}

GameController::GameController()
{
	setCurGameState(GAME_STATE::LOGO);
}

GameController::~GameController()
{
	CC_SAFE_DELETE(_controller);
}

void GameController::goState(const GAME_STATE state)
{
	setCurGameState(state);
	switch (state)
	{
	case GAME_STATE::LOGO:
		logo();
		break;
	case GAME_STATE::MENU:
		menu();
		break;
	case GAME_STATE::MAP:
		map();
		break;
	case GAME_STATE::GAME:
		//test();
		game(0);
		break;
	case GAME_STATE::OVER:
		over();
		break;
	}
}

void GameController::logo()
{
	auto logo = GameLogo::createScene();
	Director::getInstance()->runWithScene(logo);
}

void GameController::menu()
{
	auto menu = GameMenu::createScene();
	this->nextScene(menu);
}

void GameController::map()
{

}

void GameController::game(const unsigned int map)
{
	auto game = GameScene::create();
	this->nextScene(game);
}

void GameController::over()
{

}

void GameController::test()
{
	auto game = test::createScene();
	this->nextScene(game);
}

void GameController::nextScene(Scene* next_scene)
{
	this->setCurScene(next_scene);
	auto trasition = TransitionCrossFade::create(1.3f,next_scene);
	Director::getInstance()->replaceScene(trasition);
}