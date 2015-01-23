#ifndef BREAK_OUT_SCENE
#define BREAK_OUT_SCENE


#include "cocos2d.h"
#include "GameWorld.h"
USING_NS_CC;

class GameScene :public Scene
{

public:
	CREATE_FUNC(GameScene);

	virtual bool init() override;

	GameScene();

	~GameScene();
private:
	
	void startGameByLevel(int);

	void initLevelDataTMX(int); 


};

#endif