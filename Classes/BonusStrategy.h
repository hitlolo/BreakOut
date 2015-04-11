#ifndef BREAK_OUT_STRATEGY
#define BREAK_OUT_STRATEGY

#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "GB2ShapeCache-x.h"

USING_NS_CC;

class Strategy
{
public:
	PhysicsSprite* createBonusSprite(b2World* world);
protected:
	virtual std::string getSpriteName() = 0;
	virtual std::string getShapeName() = 0;
};

class FruitStrategy :public Strategy
{
//public:
//	FruitStrategy();
//	~FruitStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
private:
	int getRandomFruit();
};

class SpeedUpStrategy :public Strategy
{
//public:
//	SpeedUpStrategy();
//	~SpeedUpStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
};

class SpeedDownStrategy :public Strategy
{
//public:
//	SpeedDownStrategy();
//	~SpeedDownStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
};

class BallBonusStrategy :public Strategy
{
//public:
//	BallBonusStrategy();
//	~BallBonusStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
};

class BarUpStrategy :public Strategy
{
//public:
//	BarUpStrategy();
//	~BarUpStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
};

class BarDownStrategy :public Strategy
{
//public:
//	BarDownStrategy();
//	~BarDownStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
};

class QuestionMarkStrategy :public Strategy
{
//public:
//	QuestionMarkStrategy();
//	~QuestionMarkStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;

private:
	int getRandomColor();
};

class ExcalmationMarkStrategy :public Strategy
{
//public:
//	ExcalmationMarkStrategy();
//	~ExcalmationMarkStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
private:
	int getRandomColor();
};

class BadThingStrategy :public Strategy
{
//public:
//	BadThingStrategy();
//	~BadThingStrategy();
private:
	virtual std::string getSpriteName() override;
	virtual std::string getShapeName() override;
private:
	int getRandomColor();
};

#endif