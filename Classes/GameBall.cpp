#include "GameBall.h"

GameBall::GameBall(b2World* world)
{
	m_world = world;
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
	if (!Sprite::init())
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
	bodyDef.position.Set(  ptm(144), ptm(256));
	auto body = m_world->CreateBody(&bodyDef);

	//b2CircleShape circle;
	//circle.m_radius = ptm(9.0) ;

	//b2FixtureDef ballShapeDef;
	//ballShapeDef.shape = &circle;
	//ballShapeDef.density = 0.0f;
	//ballShapeDef.friction = 0.0f;
	//ballShapeDef.restitution = 1.0f;
	//body->CreateFixture(&ballShapeDef);
	GB2ShapeCache::getInstancs()->addFixturesToBody(body, "Bar4");
	this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);
}

void GameBall::beReady()
{
	//initSelfImage();
	initPhysicsAttributes();
}

void GameBall::startGame()
{

}