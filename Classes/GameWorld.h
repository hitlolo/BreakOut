#ifndef BREAK_OUT_WORLD
#define BREAK_OUT_WORLD

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameSound.h"
#include "GameData.h"
USING_NS_CC;
USING_NS_UI;

class GameWorld :public Scene
{
public:
	CREATE_FUNC(GameWorld);

	virtual bool init() override;

	GameWorld();

	~GameWorld();
private:
	void addBackground();

	void initPhysicsWorld();


};

#endif