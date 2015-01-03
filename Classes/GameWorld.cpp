#include "GameWorld.h"


bool GameWorld::init()
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	addBackground();
	initPhysicsWorld();

	return true;
}

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

void GameWorld::addBackground()
{
	auto background = Scale9Sprite::createWithSpriteFrameName("res/menuPanel.png");
	background->setContentSize(Size(288, 512));
	background->setPosition(CENTER);
	this->addChild(background);

}

void GameWorld::initPhysicsWorld()
{
	//1.gravity
	Vec2 gravity = Vec2(0.0f, 0.0f);
	this->getPhysicsWorld()->setGravity(gravity);
	//2.walls
#if 1
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 1.0f);
	auto node = Node::create();
	node->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	node->setPhysicsBody(body);
	this->addChild(node);

}