#include  "BonusDealer.h"


BonusDealer* BonusDealer::_bonusDealer = nullptr;

BonusDealer* BonusDealer::getInstance()
{
	if (_bonusDealer == nullptr)
	{
		_bonusDealer = new BonusDealer();
		return _bonusDealer;
	}
	else
		return _bonusDealer;
}


void  BonusDealer::resetCollideFilter(PhysicsSprite* originSprite)
{
	b2Filter filter;
	filter.groupIndex = -1;
	filter.categoryBits = 0;
	filter.maskBits = 0;
	originSprite->getB2Body()->GetFixtureList()->SetFilterData(filter);
}

void  BonusDealer::cleanupBonusSprite(PhysicsSprite* originSprite)
{
	auto  fadeout = FadeOut::create(0.2f);
	//	auto  fadein = FadeIn::create(0.05f);
	//	auto  repeat = Repeat::create(Sequence::create(fadeout, fadein, nullptr), 2);
	//	auto action = Spawn::create(scaledown, fade, nullptr);
	auto clean = CallFunc::create(CC_CALLBACK_0(PhysicsSprite::dump, originSprite));

	auto sequence = Sequence::create(fadeout, clean, nullptr);
	originSprite->runAction(sequence);
}


void BonusDealer::dealFruitBonus(PhysicsSprite* originSprite, HudLayer* hud)
{
	//1.update score
	//2.jump a label
	//3.destory and clean up

	//0.
	this->resetCollideFilter(originSprite);
	//1.
	int score = 100;
	hud->updateScore(score);
	//2.
	Point position = originSprite->getPosition();
	hud->showBonusText(position,"+100");

	//3.
	this->cleanupBonusSprite(originSprite);


}

void BonusDealer::dealSpeedUpBonus(GameBall* ball, PhysicsSprite* originSprite, HudLayer* hud)
{
	//0.
	this->resetCollideFilter(originSprite);
	//1.modify ball speed
	//2.hud shows
	unsigned bonus_time = 10;
	int speed_state = ball->speedUp(bonus_time);

	if (speed_state == -1)
	{
		//means shut down the timing
		hud->showBonusTime(0);
	}
	else
		hud->showBonusTime(bonus_time);

	//2.
	Point position = originSprite->getPosition();
	hud->showBonusText(position, "speed up");

	//3.clean
	this->cleanupBonusSprite(originSprite);
}

void BonusDealer::dealSpeedDownBonus(GameBall* ball, PhysicsSprite* originSprite, HudLayer* hud)
{
	//0.
	this->resetCollideFilter(originSprite);
	//1.modify ball speed
	//2.hud shows
	unsigned bonus_time = 10;
	int speed_state = ball->speedDown(bonus_time);
	if (speed_state == -1)
	{
		//means shut down the timing
		hud->showBonusTime(0);
	}
	else
		hud->showBonusTime(bonus_time);

	//2.
	Point position = originSprite->getPosition();
	hud->showBonusText(position, "speed down");

	//3.clean
	this->cleanupBonusSprite(originSprite);
}

void BonusDealer::dealPaddleUpBonus(GamePaddle* paddle, PhysicsSprite* originSprite, HudLayer* hud)
{
	//0.
	this->resetCollideFilter(originSprite);
	//1.modify paddle speed
	unsigned bonus_time = 10;
	int paddle_state = paddle->paddleUp(bonus_time);
	if (paddle_state == -1)
	{
		//means shut down the timing
		hud->showBonusTime(0);
	}
	else
		hud->showBonusTime(bonus_time);
	//2.hud shows
	//2.
	Point position = originSprite->getPosition();
	hud->showBonusText(position, "paddle up");
	

	//3.clean
	this->cleanupBonusSprite(originSprite);
}

void BonusDealer::dealPaddleDownBonus(GamePaddle* paddle, PhysicsSprite* originSprite, HudLayer* hud)
{
	//0.
	this->resetCollideFilter(originSprite);
	//1.modify paddle speed
	unsigned bonus_time = 10;
	int paddle_state = paddle->paddleDown(bonus_time);
	if (paddle_state == -1)
	{
		//means shut down the timing
		hud->showBonusTime(0);
	}
	else
		hud->showBonusTime(bonus_time);
	//2.hud shows
	//2.
	Point position = originSprite->getPosition();
	hud->showBonusText(position, "paddle down");

	//3.clean
	this->cleanupBonusSprite(originSprite);
}