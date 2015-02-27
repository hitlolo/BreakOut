#include "GameBrick.h"

GameBrick::GameBrick()
	:lifePoint(1)
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
	this->initPhysics(world);
	this->initLife(def);
}

void GameBrick::initImage(Value &def)
{
	auto brickDef = def.asValueMap();
	float positionX = brickDef["x"].asInt();
	float positionY = brickDef["y"].asInt();
	float rotation = brickDef["rotation"].asFloat();
	std::string filename = getBrickColor(def);
	this->initWithSpriteFrameName(filename.c_str());
	//this->setAnchorPoint(Point(0, 0));
	this->setPosition(Point(positionX, positionY));
	this->setRotation(rotation);
}

bool GameBrick::initType(Value& def)
{
	auto brickDef = def.asValueMap();
	is_longBrick = brickDef["type"].asBool();

	return is_longBrick;
}

void GameBrick::initLife(Value&  def)
{
	auto brickDef = def.asValueMap();
	lifePoint = brickDef["life"].asInt();
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

void GameBrick::initPhysics(b2World* world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.linearDamping = 0.0f;
	bodyDef.angularDamping = 0.0f;
	bodyDef.fixedRotation = true;
	
	bodyDef.position.Set(ptm(getPosition().x), ptm(getPosition().y));
	auto body = world->CreateBody(&bodyDef);

	GB2ShapeCache::getInstancs()->addFixturesToBody(body, getShapeName());
	this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);
	this->setIgnoreBodyRotation(false);

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