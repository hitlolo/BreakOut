#include "BonusStrategy.h"

//strategy
PhysicsSprite* Strategy::createBonusSprite(b2World* world)
{
	std::string frame_name = this->getSpriteName();
	PhysicsSprite* sprite = PhysicsSprite::createWithSpriteFrameName(frame_name.c_str());
	std::string shape_name = this->getShapeName();
	
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.0f;
	//bodyDef.fixedRotation = true;
	//bodyDef.gravityScale = 0.0f;
	bodyDef.userData = sprite;
	auto body = world->CreateBody(&bodyDef);
	GB2ShapeCache::getInstance()->addFixturesToBody(body, shape_name);
	sprite->setB2Body(body);
	sprite->setPTMRatio(PTM_RATIO);
	sprite->setIgnoreBodyRotation(false);
	return sprite;
}


///fruit

//FruitStrategy::FruitStrategy()
//	:type(0)
//{
//
//}
//
//FruitStrategy::~FruitStrategy()
//{
//
//}

std::string FruitStrategy::getSpriteName()
{
	int type = this->getRandomFruit();
	switch (type)
	{
	case 0:
		return std::string("Fruit_Apple.png");
		break;
	case 1:
		return std::string("Fruit_Orange.png");
		break;
	case 2:
		return std::string("Fruit_Banana.png");
		break;
	case 3:
		return std::string("Fruit_Grape.png");
		break;
	}
}

std::string FruitStrategy::getShapeName()
{
	return std::string("fruit");
}


int FruitStrategy::getRandomFruit()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_int_distribution<int> dist(0, 3);
	return dist(mt);
}

///end of fruit 


///speed up
std::string SpeedUpStrategy::getSpriteName()
{
	return std::string("speedUp.png");
}

std::string SpeedUpStrategy::getShapeName()
{
	return std::string("bonus_speed_up");
}



///speed down
std::string SpeedDownStrategy::getSpriteName()
{
	return std::string("speedDown.png");
}

std::string SpeedDownStrategy::getShapeName()
{
	return std::string("bonus_speed_down");
}


///BallBonusStrategy
std::string BallBonusStrategy::getSpriteName()
{
	return std::string("ballUp.png");
}

std::string BallBonusStrategy::getShapeName()
{
	return std::string("bonus_ballup");
}

///BarUpStrategy
std::string BarUpStrategy::getSpriteName()
{
	return std::string("paddleUp.png");
}

std::string BarUpStrategy::getShapeName()
{
	return std::string("bonus_bar_up");
}

///BarDownStrategy
std::string BarDownStrategy::getSpriteName()
{
	return std::string("paddleDown.png");
}

std::string BarDownStrategy::getShapeName()
{
	return std::string("bonus_bar_down");
}

///QuestionMarkStrategy

std::string QuestionMarkStrategy::getSpriteName()
{
	int type = this->getRandomColor();
	if (type == 0)
		return std::string("StoneQuestionMark_Blue.png");
	else
		return std::string("StoneQuestionMark_Purple.png");
}

std::string QuestionMarkStrategy::getShapeName()
{
	return std::string("bonus_question");
}

int QuestionMarkStrategy::getRandomColor()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_int_distribution<int> dist(0, 1);
	return dist(mt);
}



///ExcalmationMarkStrategy

std::string ExcalmationMarkStrategy::getSpriteName()
{
	int type = this->getRandomColor();
	if (type == 0)
		return std::string("StoneExclamationMark_Blue.png");
	else
		return std::string("StoneExclamationMark_Purple.png");
}

std::string ExcalmationMarkStrategy::getShapeName()
{
	return std::string("bonus_excalmation");
}

int ExcalmationMarkStrategy::getRandomColor()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_int_distribution<int> dist(0, 1);
	return dist(mt);
}



///BadThingStrategy

std::string BadThingStrategy::getSpriteName()
{
	int type = this->getRandomColor();
	if (type == 0)
		return std::string("StoneX_Blue.png");
	else if (type == 1)
		return std::string("StoneX_DarkGray.png");
	else
		return std::string("StoneX_Green.png");
}

std::string BadThingStrategy::getShapeName()
{
	return std::string("bonus_bad");
}

int BadThingStrategy::getRandomColor()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_int_distribution<int> dist(0, 2);
	return dist(mt);
}