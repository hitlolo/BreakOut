#include "GameBall.h"

bool GameBall::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	initSelf();
	initPhysicsAttributes();
	return true;
}



void  GameBall::initSelf()
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

	PhysicsBody *body = PhysicsBody::create();
	PhysicsShape *shape = PhysicsShapeCircle::create(8.0f, PHYSICSBODY_MATERIAL_BREAKOUT);
//	shape->setDensity(1.0f);
//	shape->setRestitution(1.0f);
//	shape->setFriction(0.0f);
	body->addShape(shape);
//	body->setDynamic(true);
//	body->setGravityEnable(true);
	this->setPhysicsBody(body);

	Vect force = Vect(50, 340);
//	body->setVelocity(force);
	body->applyImpulse(force);
}