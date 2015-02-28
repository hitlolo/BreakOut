#include "GameBall.h"

GameBall::GameBall(b2World* world)
	:isStarted(false)
	, m_world(world)
{
	
}

GameBall::~GameBall()
{

}

GameBall* GameBall::create(b2World* world)
{
	GameBall * ret = new (std::nothrow) GameBall(world);
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameBall::init()
{
	if (!PhysicsSprite::init())
	{
		return false;
	}
	beReady();
	return true;
}



void  GameBall::initSelfImage()
{
	std::string file_name = selectRandomColor();
	this->initWithSpriteFrameName(file_name);

}

std::string GameBall::selectRandomColor()
{
	srand((unsigned)time(NULL));
	int color = ((int)rand()) % 7;
	switch (color)
	{
	case 0:
		return std::string("Ball_Blue.png");
	case 1:
		return std::string("Ball_Brown.png");
	case 2:
		return std::string("Ball_Darkgray.png");
	case 3:
		return std::string("Ball_LightGray.png");
	case 4:
		return std::string("Ball_Purple.png");
	case 5:
		return std::string("Ball_Red.png");
	case 6:
		return std::string("Ball_Yellow.png");
	}
}

void  GameBall::initPhysicsAttributes()
{

	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.0f;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(  ptm(288), ptm(96) );
	auto body = m_world->CreateBody(&bodyDef);

	GB2ShapeCache::getInstancs()->addFixturesToBody(body, "ball");
	this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);
	this->setIgnoreBodyRotation(false);
}


void GameBall::beReady()
{
	initSelfImage();
	initPhysicsAttributes();

}

void GameBall::startGame()
{
	this->getB2Body()->SetLinearVelocity(b2Vec2(0, 25));
	this->getB2Body()->SetAngularVelocity(5.0f);
	this->setStarted(true);
//	this->scheduleUpdate();
}

//void GameBall::update(float time)
//{
////	m_streak->setPosition(this->convertToWorldSpace(Vec2::ZERO));
//	sp->setPosition(getPosition());
//}