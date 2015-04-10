#ifndef BREAK_OUT_STRATEGY
#define BREAK_OUT_STRATEGY

#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "GB2ShapeCache-x.h"

USING_NS_CC;

class Strategy
{
public:
	virtual PhysicsSprite* createBonusSprite() = 0;
};

class FruitStrategy :public Strategy
{
public:
	FruitStrategy();
	~FruitStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
private:
	int getRandomFruit();
};

class SpeedUpStrategy :public Strategy
{
public:
	SpeedUpStrategy();
	~SpeedUpStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class SpeedDownStrategy :public Strategy
{
public:
	SpeedDownStrategy();
	~SpeedDownStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class BallBonusStrategy :public Strategy
{
public:
	BallBonusStrategy();
	~BallBonusStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class BarUpStrategy :public Strategy
{
public:
	BarUpStrategy();
	~BarUpStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class BarDownStrategy :public Strategy
{
public:
	BarDownStrategy();
	~BarDownStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class QuestionMarkStrategy :public Strategy
{
public:
	QuestionMarkStrategy();
	~QuestionMarkStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class ExcalmationMarkStrategy :public Strategy
{
public:
	ExcalmationMarkStrategy();
	~ExcalmationMarkStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

class BadThingStrategy :public Strategy
{
public:
	BadThingStrategy();
	~BadThingStrategy();
	virtual PhysicsSprite* createBonusSprite() override;
};

#endif