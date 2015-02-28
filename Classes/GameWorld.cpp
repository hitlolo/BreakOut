#include "GameWorld.h"


GameWorld* GameWorld::create(int level)
{
	GameWorld * ret = new (std::nothrow) GameWorld();
	if (ret && ret->init(level))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool GameWorld::init(int level)
{
	if (!Layer::init())
	{
		return false;
	}
	
	addBackground();
	addTouch();
	createPhysicsWorld();
	createEdgeBox();
	initLevelData(level);
	addBall();
	addPaddle();
	addStreak();
	return true;
	

}




GameWorld::GameWorld()
: m_world(nullptr)
, m_debugDraw(nullptr)
, m_ball(nullptr)
, m_paddle(nullptr)
, m_maxSpeed(25)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	originPoint = Director::getInstance()->getVisibleOrigin();

	isStarted = false;
	
	GB2ShapeCache::getInstancs()->addShapesWithFile("breakout.plist");
}

GameWorld::~GameWorld()
{

	CC_SAFE_DELETE(m_world);
	CC_SAFE_DELETE(m_debugDraw);
}

void GameWorld::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void GameWorld::addBackground()
{
	auto background = Scale9Sprite::createWithSpriteFrameName("res/panel.png");
	background->setContentSize(Size(576, 1024));
	background->setPosition(CENTER);
	this->addChild(background);

}

void GameWorld::createPhysicsWorld()
{
	//1.gravity
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	m_world = new b2World(gravity);

	
	//2.debug
#if 1
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);   //这里新建一个 debug渲染模块  
	m_world->SetDebugDraw(m_debugDraw);    //设置  
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//b2Draw::e_centerOfMassBit;   //获取需要显示debugdraw的块  
	//b2Draw::e_aabbBit;  //AABB块  
	//b2Draw::e_centerOfMassBit; 物体质心  
	//b2Draw::e_jointBit;  //关节  
	//b2Draw::e_shapeBit;   形状  
	m_debugDraw->SetFlags(flags);   //需要显示那些东西  
#endif

	
}

void GameWorld::createEdgeBox()
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	groundBodyDef.angularDamping = 0.0f;
	groundBodyDef.linearDamping = 0.0f;
	std::string *ground = new std::string("ground");
	groundBodyDef.userData = ground;

	m_groundBody = m_world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	boxShapeDef.restitution = 0;
	boxShapeDef.friction = 0;
	//wall definitions
	//BOTTOM
	groundEdge.Set(b2Vec2(0, 0), b2Vec2( ptm(visibleSize.width) , 0));
	m_groundBody->CreateFixture(&boxShapeDef);
	// top
	groundEdge.Set(b2Vec2(0, ptm(visibleSize.height)), b2Vec2( ptm(visibleSize.width), ptm(visibleSize.height) ));
	m_groundBody->CreateFixture(&boxShapeDef);

	// left
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, ptm(visibleSize.height)));
	m_groundBody->CreateFixture(&boxShapeDef);

	// right
	groundEdge.Set(b2Vec2( ptm(visibleSize.width), 0), b2Vec2( ptm(visibleSize.width), ptm(visibleSize.height)));
	m_groundBody->CreateFixture(&boxShapeDef);
	
}


bool GameWorld::initLevelData(int level)
{
	m_brickLayer = BrickLayer::create(level, getPhysicsWorld());
	this->addChild(m_brickLayer);
	return true;
}

b2World* GameWorld::getPhysicsWorld() const
{
	return  m_world;
}

void GameWorld::addBall()
{
	m_ball = GameBall::create(m_world);
	this->addChild(m_ball);
}

void GameWorld::addPaddle()
{
	m_paddle = GamePaddle::create(m_world,m_groundBody);
	this->addChild(m_paddle);
}

void GameWorld::addTouch()
{
	auto touchLayer = TouchLayer::create();
	touchLayer->setDelegator(this);
	this->addChild(touchLayer);
}

void GameWorld::addStreak()
{
	//	auto texture = SpriteFrameCache::getInstance()->getSpriteFrameByName("Ball_Darkgray.png");
	m_streak = MotionStreak::create(0.5f, 2.0f, 12.0f, Color3B(200, 200, 200), "Ball_LightGray.png");
	m_streak->setPosition(m_ball->getPosition());
//	m_streak->setAnchorPoint(Point(0, 0));
	this->addChild(m_streak);
//	CCLOG("%f,%f", m_streak->getPosition().x, m_streak->getPosition().y);
//	sp = Sprite::createWithSpriteFrameName("Ball_Darkgray.png");
//	this->addChild(sp);
//	sp->setPosition(Point(0, 32));
}


#if 1
void GameWorld::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

	kmGLPushMatrix();
	m_world->DrawDebugData();

	kmGLPopMatrix();

	CHECK_GL_ERROR_DEBUG();
}
#endif

void GameWorld::update(float dt)
{
	m_world->Step(dt, 10, 10);
	m_world->ClearForces();
	b2Vec2 velocity = m_ball->getB2Body()->GetLinearVelocity();
	float32 speed = velocity.Length();
	if (speed > m_maxSpeed) {
		m_ball->getB2Body()->SetLinearDamping(0.5);
		//m_ball->getB2Body()->SetLinearVelocity(b2Vec2(0, 25));
	}
	else if (speed < m_maxSpeed) {
		m_ball->getB2Body()->SetLinearDamping(0.0);
	}

	//streak
	m_streak->setPosition(m_ball->getPosition());

	//float angle =	m_ball->getB2Body()->GetAngle();
	////CCLOG("ANGLE:%f",angle);
}

void GameWorld::onGameStart()
{
	if (m_ball->getStarted())
		return;
	else
	{
		m_ball->startGame();
		this->setStarted(true);
	}
}

void GameWorld::onReturn()
{
	GameController::getInstance()->popScene();
}

void GameWorld::onPaddleBeginMove(const std::vector<Touch*>& touches)
{
	m_paddle->onBeginMove(touches);
}
void GameWorld::onPaddleMove(const std::vector<Touch*>& touches)
{
	m_paddle->onMove(touches);
}
void GameWorld::onPaddleEndMove()
{
	m_paddle->onMoveEnd();
}
void GameWorld::onPaddleCancelMove()
{
	m_paddle->onMoveCancel();
}