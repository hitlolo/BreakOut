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
	
//	addBackground();
	addTouch();
	createPhysicsWorld();
	createEdgeBox();
	addBrickLayer(level);
	addBall();
	addPaddle();
	
	//auto   shatter = GameShatter::create(m_world);
	//this->addChild(shatter);
	//shatter->setPosition(CENTER);
	//V3F_C4B_T2F_POLY s{nullptr,0};
	//auto sp = ShatterSprite::create(s, "grey_button08.png");
	//this->addChild(sp);
	//sp->setPosition(CENTER);

#if 1
	m_draw = DrawNode::create();
	this->addChild(m_draw,100);
#endif

	return true;
	
}


GameWorld::GameWorld()
: m_world(nullptr)
, m_debugDraw(nullptr)
, m_ball(nullptr)
, m_paddle(nullptr)
, m_streak(nullptr)
, m_particle(nullptr)
, m_contact(nullptr)
//, m_maxSpeed(25)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	originPoint = Director::getInstance()->getVisibleOrigin();
	isStarted = false;	
	GB2ShapeCache::getInstancs()->addShapesWithFile("breakout.plist");
	setSoundEngine(GameSound::getInstance());
}

GameWorld::~GameWorld()
{

	CC_SAFE_DELETE(m_world);
	CC_SAFE_DELETE(m_debugDraw);
	CC_SAFE_DELETE(m_contact);
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
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	

	
	//2.debug
#if 1
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);   //这里新建一个 debug渲染模块  
	m_world->SetDebugDraw(m_debugDraw);    //设置  
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_centerOfMassBit;   //获取需要显示debugdraw的块  
	//b2Draw::e_aabbBit;  //AABB块  
	//flags += b2Draw::e_centerOfMassBit; //物体质心
	//flags += b2Draw::e_jointBit;  //关节  
	//b2Draw::e_shapeBit;   形状  
	m_debugDraw->SetFlags(flags);   //需要显示那些东西  
#endif

	//add contact listener
	m_contact = new ContactListener();
	m_world->SetContactListener(m_contact);
	
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
	boxShapeDef.filter.categoryBits = 8;
	groundEdge.Set(b2Vec2(0, 0), b2Vec2( ptm(visibleSize.width) , 0));
	m_groundBody->CreateFixture(&boxShapeDef);

	boxShapeDef.filter.categoryBits = 16;
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


bool GameWorld::addBrickLayer(int level)
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
	m_particle = ParticleSystemQuad::create("motionstreak.plist");
	this->addChild(m_particle);
	m_particle->setPosition(m_ball->getPosition());
	
	m_streak = MotionStreak::create(0.5f, 2.0f, 12.0f, Color3B(200, 200, 200), "Ball_LightGray.png");
	m_streak->setAnchorPoint(Point(0.5, 0.5));
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

//deal contact
void GameWorld::logic()
{
	std::vector<CustomContact>& contactVector = this->m_contact->getContactVector();
	for (auto contact : contactVector)
	{
		auto collideType = contact.getCollideType();
		//play melody
		switch (collideType)
		{
			case COLLIDE_TYPE::BALL_BRICK:
			{
				//MELODY
				auto brick = (GameBrick*)(contact.getBrickFixture()->GetBody()->GetUserData());
				//LIFE
				b2Vec2 point = contact.getContactPoint();
				//CCLOG("%f,%f", point.x, point.y);
				//Vec2 draw_point = Vec2(mtp(point.x), mtp(point.y));
				////CCLOG("%f,%f,draw_point", draw_point.x, draw_point.y);

				//m_draw->drawCircle(draw_point, 8.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
				//CCLOG("%f,%f,draw_point", draw_point.x, draw_point.y);
				//m_draw->drawRect(Vec2(23, 23), Vec2(7, 7), Color4F(1, 1, 0, 1));

				brick->collision(point);
				
				break;
			}
			case COLLIDE_TYPE::BALL_PADDLE:
			{
				getSoundEngine()->playMelody(MELODY::XI);
				break;
			}
			default:
				return;
			
		}
	}


}

void GameWorld::update(float dt)
{
	m_world->Step(dt, 10, 10);
	logic();
	m_world->ClearForces();
	
	if (m_streak)
	{
		m_streak->setPosition(m_ball->getPosition());
	}
	if (m_particle)
	{
		m_particle->setPosition(m_ball->getPosition());
	}
	
	//contact
	
}

void GameWorld::onGameStart()
{
	if (m_ball->getStarted())
		return;
	else
	{
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