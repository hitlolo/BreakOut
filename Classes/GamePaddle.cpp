#include "GamePaddle.h"

GamePaddle::GamePaddle(b2World* world)
{
	m_world = world;
}

GamePaddle::~GamePaddle()
{

}

GamePaddle* GamePaddle::create(b2World* world)
{
	GamePaddle * ret = new (std::nothrow) GamePaddle(world);
	if (ret && ret->init())
	{
		ret->Sprite::autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GamePaddle::init()
{
	if (!Scale9Sprite::init())
	{
		return false;
	}
	initSelfImage();

	return true;
}


void  GamePaddle::initSelfImage()
{
	this->Sprite::initWithSpriteFrameName(selectRandomFile());
	this->Sprite::setContentSize(NORMAL_SIZE);
	this->initPhysicsAttributes();
}

std::string  GamePaddle::selectRandomFile()
{
	srand((unsigned)time(NULL));
	int color = ((int)rand()) % 6;
	color += 4;
	String* file = String::createWithFormat("Bar%d.png", color);
	return file->getCString(); 
}

void GamePaddle::initPhysicsAttributes()
{
	//auto body = PhysicsBody::create();
	//ShapeCache::getInstance()->addShapesWithFile("normalPaddleShape.plist", body);	//this->setB2Body(body);
}