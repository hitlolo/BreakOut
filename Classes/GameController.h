#ifndef BREAK_OUT_CONTROLLER
#define BREAK_OUT_CONTROLLER

#include "cocos2d.h"
#include "GameData.h"
#include "GameLogo.h"
#include "GameMenu.h"
#include "GameScene.h"
#include  "test.h"


USING_NS_CC;

class GameController
{

public:
	static GameController* getInstance();

	GameController();

	~GameController();

	void goState(const GAME_STATE = GAME_STATE::LOGO);

private:
	static GameController* _controller; 

	void nextScene(Scene*);	

	CC_SYNTHESIZE(GAME_STATE, curGameState, CurGameState);

	CC_SYNTHESIZE(Scene*, curScene, CurScene);

private:

	void logo();

	void menu();

	void map();

	void game(const unsigned int map);

	void over();

	void test();
};

#endif