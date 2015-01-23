#include "GamePaddle.h"

bool GamePaddle::init()
{
	if (!Scale9Sprite::init())
	{
		return false;
	}
	initPaddle();

	return true;
}

void  GamePaddle::initPaddle()
{
	this->initWithSpriteFrameName(selectRandomFile());
	this->setContentSize(NORMAL_SIZE);
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
	auto body = PhysicsBody::create();
	ShapeCache::getInstance()->addShapesWithFile("normalPaddleShape.plist", body);	this->setPhysicsBody(body);
}