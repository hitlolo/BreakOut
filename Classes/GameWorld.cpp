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
	
	//addBackground();
	addHUD();
	addTouchLayer();

	createPhysicsWorld();
	createEdgeBox();
	addBrickLayer(level);
	addBall();
	addPaddle();
		
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
, m_hud(nullptr)
//, m_maxSpeed(25)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	originPoint = Director::getInstance()->getVisibleOrigin();
	isStarted = false;	
	//shape cache ready
	
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
	//full screen
	background->setContentSize(Size(576, 1024));
	background->setPosition(CENTER);
	this->addChild(background);

}

void GameWorld::addHUD()
{
	m_hud = HudLayer::create();
	this->addChild(m_hud);
}

void GameWorld::createPhysicsWorld()
{
	//1.gravity
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	
	//2.debug draw
#if 1
	m_debugDraw = new GLESDebugDraw(PTM_RATIO);   //这里新建一个 debug渲染模块  
	m_world->SetDebugDraw(m_debugDraw);    //设置  
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_centerOfMassBit;   //获取需要显示debugdraw的块  
	//flags += b2Draw::e_aabbBit;  //AABB块  
	//flags += b2Draw::e_centerOfMassBit; //物体质心
	//flags += b2Draw::e_jointBit;  //关节  
	//b2Draw::e_shapeBit;   形状  
	m_debugDraw->SetFlags(flags);   //需要显示那些东西  
#endif

	///3.add contact listener
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

void GameWorld::addTouchLayer()
{
	auto touchLayer = TouchLayer::create();
	touchLayer->setDelegator(this);
	this->addChild(touchLayer);
}

void GameWorld::addStreak()
{
	//particle
	m_particle = ParticleSystemQuad::create("motionstreak.plist");
	this->addChild(m_particle);
	m_particle->setPosition(m_ball->getPosition());
	
	//streak
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
	this->dealContact();
}

void GameWorld::dumpOutsideBodies()
{
	std::vector<b2Body*> eraser;
	for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		b2Vec2 location = b->GetPosition();
		if ( location.y < 0 && (b->GetFixtureList()->GetFilterData().categoryBits!=(uint16)COLLIDE_BIT::SHATTER))
		{
			eraser.push_back(b);
		}
	}

	for (auto body : eraser)
	{
		auto sprite = (Sprite*)body->GetUserData();
	
		body->SetUserData(nullptr);
		m_world->DestroyBody(body);
		if (sprite)
			sprite->removeFromParentAndCleanup(true);
	}
}

void GameWorld::update(float dt)
{
	m_world->Step(dt, 10, 10);
	this->logic();
	m_world->ClearForces();
	dumpOutsideBodies();
	if (m_streak)
	{
		m_streak->setPosition(m_ball->getPosition());
	}
	if (m_particle)
	{
		m_particle->setPosition(m_ball->getPosition());
	}
	
	
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


void GameWorld::brickBomb(GameBrick* brick, b2Vec2 point)
{
	GameShatter* shatter = GameShatter::create(brick, point);
	this->addChild(shatter);
	shatter->bomb();
}

void GameWorld::dealContact()
{
	std::vector<CustomContact> contactVector = this->m_contact->getContactVector();
	std::map<GameBrick*, b2Vec2> undealCollideBrick;
	for (auto contact : contactVector)
	{
		auto collideType = contact.getCollideType();
		
		//play melody
		switch (collideType)
		{
		case COLLIDE_TYPE::BALL_BRICK:
		{
			//buffer contact
			auto brick = (GameBrick*)(contact.getBrickFixture()->GetBody()->GetUserData());
			b2Vec2 point = contact.getContactPoint();
			undealCollideBrick[brick] = point;
			break;
		}
		case COLLIDE_TYPE::BALL_PADDLE:
		{
			getSoundEngine()->playMelody(MELODY::XI);
			break;
		}
		case COLLIDE_TYPE::BALL_WALL:
		{
			getSoundEngine()->playMelody(MELODY::FA);
			break;
		}
		default:
			return;

		}
	}

	//deal buffer contact bricks
	for (auto collide_brick : undealCollideBrick)
	{
		auto brick = collide_brick.first;
		auto point = collide_brick.second;
		//1. brick jump, lifepoint minus
		int brick_hp = brick->collision(point);
		//2. scroe up
		m_hud->updateScore(brick->getCoinPoint());
		//3. brick bomb
		if (brick_hp <= 0)
		{
			Point brick_position = brick->getPosition();
			brickBomb(brick, point);
			Lottery  type = GameLottery::getInstance()->lottery();
			if (type != LOTTERY::NONE)
			{
	
				auto bonus = BonusCreator::getInstance()->createBonus(type, m_world, brick_position);
				this->addChild(bonus);
			}
		}
		
		
	}

	//undealCollideBrick.clear();

}
