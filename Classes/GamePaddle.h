#ifndef BREAK_OUT_PADDLE
#define BREAK_OUT_PADDLE

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameData.h"
#include "ShapeCache.h"

USING_NS_CC;
USING_NS_UI;

#define NORMAL_SIZE Size(96,32)
#define MIN_SIZE Size(64,32)
#define MAX_SIZE Size(128,32)

class GamePaddle :public Scale9Sprite
{
public:
	CREATE_FUNC(GamePaddle);
	
	bool init() override;

private:
	std::string selectRandomFile();

	void initPhysicsAttributes();

	void initPaddle();

};

#endif