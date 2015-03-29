#include "GameBrick.h"

GameBrick::GameBrick()
	:hpPoint(1)
	, is_longBrick(false)
{

}

GameBrick::~GameBrick()
{

}

GameBrick* GameBrick::create(b2World* world,Value &def)
{
	GameBrick * ret = new (std::nothrow) GameBrick();
	if (ret && ret->init(world,def))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameBrick::init(b2World* world, Value &def)
{
	if (!PhysicsSprite::init())
	{
		return false;
	}
	initBrick(world,def);
	return true;
}

void GameBrick::initBrick(b2World* world, Value& def)
{
	this->initImage(def);
	this->initHP(def);
	this->initType(def);
	this->initPhysics(world, def);	
	

	
	this->initMelodyType(def);
	this->setOriginLocation();
//	this->scheduleUpdate();
}

void GameBrick::initImage(Value &def)
{
	auto brickDef = def.asValueMap();
	std::string filename = getBrickColor(def);
	this->initWithSpriteFrameName(filename.c_str());
//	float positionX = brickDef["x"].asInt();
//	float positionY = brickDef["y"].asInt();
//	this->setPosition(Point(positionX, positionY));
//	this->setAnchorPoint(Point(0.0, 0.0));
}

void GameBrick::initType(Value& def)
{
	auto brickDef = def.asValueMap();
	is_longBrick = brickDef["type"].asBool();
}

void GameBrick::initHP(Value&  def)
{
	auto brickDef = def.asValueMap();
	hpPoint = brickDef["life"].asInt();
}

void GameBrick::initMelodyType(Value& def)
{
	auto brickDef = def.asValueMap();
	auto color = brickDef["color"].asString();
	if (color == "white")
		this->melodyType = MELODY::SO;
	else if (color == "blue")
		this->melodyType = MELODY::FA;
	else if (color == "yellow")
		this->melodyType = MELODY::RE;
	else if (color == "red")
		this->melodyType = MELODY::DO;
	else if (color == "purple")
		this->melodyType = MELODY::LA;
	else if (color == "green")
		this->melodyType = MELODY::MI;
}

melody& GameBrick::getMelodyType()
{
	return this->melodyType;
}

std::string GameBrick::getBrickColor(Value &def)
{
	auto brickDef = def.asValueMap();
	bool type = brickDef["type"].asBool();
	if (type)
	{
		return getLongBrickColor(def);
	}
	else
	{
		return getShortBrickColor(def);
	}
}

std::string GameBrick::getLongBrickColor(Value &def)
{
	auto brickDef = def.asValueMap();
	auto color = brickDef["color"].asString();
	if (color == "white")
		return std::string("element_grey_rectangle_glossy.png");
	else if (color == "blue")
		return std::string("element_blue_rectangle_glossy.png");
	else if (color == "yellow")
		return std::string("element_yellow_rectangle_glossy.png");
	else if (color == "red")
		return std::string("element_red_rectangle_glossy.png");
	else if (color == "purple")
		return std::string("element_purple_rectangle_glossy.png");
	else if (color == "green")
		return std::string("element_green_rectangle_glossy.png");
}

std::string GameBrick::getShortBrickColor(Value &def)
{
	auto brickDef = def.asValueMap();
	auto color = brickDef["color"].asString();
	if (color == "white")
		return std::string("element_grey_square_glossy.png");
	else if (color == "blue")
		return std::string("element_blue_square_glossy.png");
	else if (color == "yellow")
		return std::string("element_yellow_square_glossy.png");
	else if (color == "red")
		return std::string("element_red_square_glossy.png");
	else if (color == "purple")
		return std::string("element_purple_square_glossy.png");
	else if (color == "green")
		return std::string("element_green_square_glossy.png");

}

void GameBrick::initPhysics(b2World* world, Value& def)
{
	auto brickDef = def.asValueMap();
	float positionX = brickDef["x"].asInt();
	float positionY = brickDef["y"].asInt();
	positionX += this->getContentSize().width / 2;
	positionY += this->getContentSize().height / 2;
	float rotation = brickDef["rotation"].asFloat();
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.0f;
	bodyDef.fixedRotation = true;
	bodyDef.gravityScale = 0.0f;
	bodyDef.angle = rotation;
	bodyDef.userData = this;
	
	bodyDef.position.Set(ptm(positionX), ptm(positionY));
	
//	bodyDef.position.Set(ptm(getPosition().x), ptm(getPosition().y));
	auto body = world->CreateBody(&bodyDef);
	GB2ShapeCache::getInstancs()->addFixturesToBody(body, getShapeName());
	this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);
	this->setIgnoreBodyRotation(false);
	//this->setPosition(Point(positionX, positionY));

	
}

std::string GameBrick::getShapeName()
{
	if (is_longBrick)
	{
		return  std::string("brick_long");
	}
	else
	{
		return std::string("brick_short");
	}
}

b2Vec2 GameBrick::getOriginLocation()
{
	return originLocation;
}

void GameBrick::setOriginLocation()
{
	originLocation = getB2Body()->GetPosition();
}

int GameBrick::collision(b2Vec2 point)
{
	//1
	PlayMelody();
	//2 shake
	shake();
	//3 check life
	if (hpPoint != 0)
	{
		hpDown();
	}
	//4 deal collision
	else if (hpPoint == 0)
	{
		
//		this->removeFromParent();
	}
	else
	{

	}
//	auto shatter = GameShatter::create(this, point);
//	this->getParent()->addChild(shatter);
//	shatter->bomb();
	//5 deal gift

//	CCLOG("%f,%f,draw_point", draw_point.x, draw_point.y);
	return hpPoint;
}

void GameBrick::PlayMelody()
{
	GameSound::getInstance()->playMelody(getMelodyType());
}

void GameBrick::shake()
{
	auto move_up = JumpBy::create(0.05f, Point(0, 0), 5,1);
	this->runAction(move_up);
//	this->setPosition(Point(100, 100));
}

void GameBrick::hpDown()
{
	this->hpPoint -= 1;
}

void GameBrick::collapse(Point point)
{

}

void GameBrick::explosion()
{

}

//void GameBrick::update(float time)
//{
//	this->setPosition(Vec2((getB2Body()->GetPosition().x) * PTM_RATIO, getB2Body()->GetPosition().y * PTM_RATIO));
//
//}