#ifndef BREAK_OUT_CONTROLLER
#define BREAK_OUT_CONTROLLER

#include "cocos2d.h"
#include "GameData.h"
#include "GameLogo.h"
#include "GameMenu.h"
#include "GameScene.h"
#include "GameMap.h"



USING_NS_CC;

class GameController
{

public:
	static GameController* getInstance();
	 GameController();
	~GameController();

public:
	//interface
	void  goState(const GAME_STATE = GAME_STATE::LOGO);
	int   getLevelPassed();
	void  setLevelPassed(int);
	
	void  backToLastScene();
	

private:
	static GameController* _controller; 
	void nextScene(Scene*);
	void pushSceneBySlideInR(Scene*);
	void pushSceneByFadeIn(Scene*);
	

private:
	void logo();
	void menu();
	void map();
	void game(const unsigned int map);
	void over();

private:
	int  level;
	CC_SYNTHESIZE(int, levelSelected, SelectedLevel);
	CC_SYNTHESIZE(GAME_STATE, curGameState, CurGameState);
	CC_SYNTHESIZE(Scene*, curScene, CurScene);
};

#endif