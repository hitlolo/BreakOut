#ifndef BREAK_OUT_SCENE
#define BREAK_OUT_SCENE


#include "cocos2d.h"
#include "GameWorld.h"
USING_NS_CC;

class GameScene :public Scene
{

public:
	
	static GameScene* create(int level);
	bool init(int level);
	GameScene();
	~GameScene();
private:	
	void startGameByLevel(int);
	void initLevelDataTMX(int);

};

#endif