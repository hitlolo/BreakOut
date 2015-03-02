#include "GameBall.h"

GameBall::GameBall(b2World* world, b2Body* ground)
	:isStarted(false)
	, m_world(world)
	, m_groundBody(ground)
	, m_mouseJoint(nullptr)
	, m_joint_x(nullptr)
	, m_maxSpeed(20)

{
	
}

GameBall::~GameBall()
{

}

GameBall* GameBall::create(b2World* world, b2Body* ground)
{
	GameBall * ret = new (std::nothrow) GameBall(world, ground);
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
	bodyDef.userData = this;
	bodyDef.position.Set(  ptm(288), ptm(96) );
	auto body = m_world->CreateBody(&bodyDef);

	GB2ShapeCache::getInstancs()->addFixturesToBody(body, "ball");
	this->setB2Body(body);
	this->setPTMRatio(PTM_RATIO);
	this->setIgnoreBodyRotation(false);

	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	jointDef.collideConnected = true;
	jointDef.Initialize(getB2Body(), m_groundBody, getB2Body()->GetWorldCenter(), worldAxis);
	m_joint_x = (b2PrismaticJoint*)getB2Body()->GetWorld()->CreateJoint(&jointDef);
}


void GameBall::beReady()
{
	initSelfImage();
	initPhysicsAttributes();

}

void GameBall::startGame()
{
	this->getB2Body()->GetWorld()->DestroyJoint(m_joint_x);
	this->getB2Body()->SetLinearVelocity(b2Vec2(0, m_maxSpeed));
	this->getB2Body()->SetAngularVelocity(5.0f);
	this->setStarted(true);
	
	this->scheduleUpdate();
}

void GameBall::update(float time)
{
	b2Vec2 velocity = getB2Body()->GetLinearVelocity();
	//ÔÈËÙÔË¶¯
	velocity.Normalize();
	velocity*= m_maxSpeed;
	this->getB2Body()->SetLinearVelocity(velocity);
}

void GameBall::onBeginMove(const  b2Vec2 position)
{
	b2MouseJointDef mouseJointDef;
	mouseJointDef.bodyA = m_groundBody;
	mouseJointDef.bodyB = getB2Body();
	mouseJointDef.target = position;
	mouseJointDef.collideConnected = true;
	mouseJointDef.maxForce = 1000.0f * getB2Body()->GetMass();

	m_mouseJoint = (b2MouseJoint *)getB2Body()->GetWorld()->CreateJoint(&mouseJointDef);
	getB2Body()->SetAwake(true);
}

void GameBall::onMove(const std::vector<Touch*>& touches)
{

	if (m_mouseJoint == NULL) return;
	for (auto &touch : touches)
	{	
		auto position = touch->getLocationInView();
		position = Director::getInstance()->convertToGL(position);
		b2Vec2 world_position = b2Vec2(ptm(position.x), ptm(position.y));
		m_mouseJoint->SetTarget(world_position);
	}
	
	
}

void GameBall::onMoveEnd()
{
	if (m_mouseJoint)
	{
		getB2Body()->GetWorld()->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
	}
}

void GameBall::onMoveCancel()
{
	if (m_mouseJoint)
	{
		getB2Body()->GetWorld()->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
	}
}