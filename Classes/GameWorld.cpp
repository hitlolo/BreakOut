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

	return true;
	

}




GameWorld::GameWorld()
: m_world(nullptr)
, m_debugDraw(nullptr)
, m_ball(nullptr)
, m_paddle(nullptr)
, m_streak(nullptr)
//, m_maxSpeed(25)
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
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);   //�����½�һ�� debug��Ⱦģ��  
	m_world->SetDebugDraw(m_debugDraw);    //����  
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_centerOfMassBit;   //��ȡ��Ҫ��ʾdebugdraw�Ŀ�  
	//b2Draw::e_aabbBit;  //AABB��  
	//flags += b2Draw::e_centerOfMassBit; //��������
	//flags += b2Draw::e_jointBit;  //�ؽ�  
	//b2Draw::e_shapeBit;   ��״  
	m_debugDraw->SetFlags(flags);   //��Ҫ��ʾ��Щ����  
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
	m_ball = GameBall::create(m_world, m_groundBody);
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
	
	m_streak = MotionStreak::create(0.5f, 2.0f, 12.0f, Color3B(200, 200, 200), "Ball_LightGray.png");
	m_streak->setPosition(m_ball->getPosition());
	this->addChild(m_streak);
	m_ball->setZOrder(m_streak->getZOrder() + 1);

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
	
	//float32 speed = velocity.Length();
	//if (speed > m_maxSpeed) {
	//	m_ball->getB2Body()->SetLinearDamping(0.5);
	//	//m_ball->getB2Body()->SetLinearVelocity(b2Vec2(0, 25));
	//}
	//else if (speed < m_maxSpeed) {
	//	m_ball->getB2Body()->SetLinearDamping(0.0);
	//}

	//streak
	if (m_streak)
	{
		m_streak->setPosition(m_ball->getPosition());
	}
	

}

void GameWorld::onGameStart()
{
	if (m_ball->getStarted())
		return;
	else
	{
		CCLOG("start");

		addStreak();
		
		this->setStarted(true);
		m_ball->startGame();
	}
}

void GameWorld::onReturn()
{
	GameController::getInstance()->popScene();
}

void GameWorld::onPaddleBeginMove(const std::vector<Touch*>& touches)
{
	for (auto &touch : touches)
	{
		auto position = touch->getLocationInView();
		position = Director::getInstance()->convertToGL(position);
		b2Vec2 world_position = b2Vec2(ptm(position.x), ptm(position.y));
		for (b2Fixture *fixture = m_paddle->getB2Body()->GetFixtureList(); fixture; fixture = fixture->GetNext())
		{
			if (fixture->TestPoint(world_position))
			{
				m_paddle->onBeginMove(world_position);
				if (!getStarted())
				{
					
					m_ball->onBeginMove(world_position);
				}
			}
		}
	}
	
	
}
void GameWorld::onPaddleMove(const std::vector<Touch*>& touches)
{
	m_paddle->onMove(touches);
	if (!getStarted())
	{
		
		m_ball->onMove(touches);
	}
		
}
void GameWorld::onPaddleEndMove()
{
	m_paddle->onMoveEnd();
	if (!getStarted())
	{
		
		m_ball->onMoveEnd();
	}
}
void GameWorld::onPaddleCancelMove()
{
	m_paddle->onMoveCancel();
	if (!getStarted())
	{
		
		m_ball->onMoveEnd();
	}
}