#ifndef BREAK_OUT_BONUS_DEALER
#define BREAK_OUT_BONUS_DEALER

#include  "cocos2d.h"
#include "PhysicsSprite.h"
#include "HudLayer.h"
#include "GameBall.h"
#include "GamePaddle.h"

USING_NS_CC;



class HudLayer;
class GameBall;

class  BonusDealer
{
private:
	static BonusDealer* _bonusDealer;
public:
	static BonusDealer* getInstance(); 
	void dealFruitBonus(PhysicsSprite* originSprite, HudLayer* hud);
	void dealSpeedUpBonus(GameBall* ball, PhysicsSprite* originSprite, HudLayer* hud);
	void dealSpeedDownBonus(GameBall* ball, PhysicsSprite* originSprite, HudLayer* hud);
	void dealPaddleUpBonus(GamePaddle* paddle, PhysicsSprite* originSprite, HudLayer* hud);
	void dealPaddleDownBonus(GamePaddle* paddle, PhysicsSprite* originSprite, HudLayer* hud);

private:
	void resetCollideFilter(PhysicsSprite* originSprite);
	void cleanupBonusSprite(PhysicsSprite* originSprite);
};





#endif