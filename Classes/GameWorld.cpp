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
	addBrickLayer(level);
	addBall();
	addPaddle();
	
	//auto   shatter = GameShatter::create(m_world);
	//this->addChild(shatter);
	//shatter->setPosition(CENTER);
	//V3F_C4B_T2F_POLY s{nullptr,0};

	//std::vector<b2Vec2> test;
	//test.resize(3);
	////-0.490350f
	//test[0] = b2Vec2(0.117446f, -0.216859f);
	//test[1] = b2Vec2(0.104618f, -0.5f);
	//test[2] = b2Vec2(0.326847f, -0.5f);
	////test[0] = b2Vec2(0.063890f, 0.288177f);
	////test[1] = b2Vec2(0.104618f, -0.5f);
	////test[2] = b2Vec2(0.326847f, -0.5f);
	////test.resize(4);
	//////-0.490350f
	////test[0] = b2Vec2(0.5, 0.5);
	////test[1] = b2Vec2(-0.5, 0.5f);
	////test[2] = b2Vec2(-0.5, -0.5f);
	////test[3] = b2Vec2(0.5, -0.5f);

	//for (int32 i = 0; i < test.size(); ++i)
	//{
	//	int32 i1 = i;
	//	int32 i2 = i + 1 < test.size() ? i + 1 : 0;
	//	b2Vec2 edge = test[i2] - test[i1];

	//	CCLOG("%f,%f,edge.LengthSquared() ", edge.LengthSquared(), 0.5f * b2_linearSlop);
	//	if (edge.LengthSquared() < 0.5f * b2_linearSlop)
	//	{
	//		CCLOG("test[%d],test[%d] small!!", i1, i2);
	//	}
	//}

	//float area = 0.0f;
	////float p1X = 0.0, p1Y = 0.0;
	////float inv3 = 1.0 / 3.0;
	//int iCycle, iCount; 
	//float iArea;
	//iArea = 0.0f;
	//iCount = test.size();

	//for (iCycle = 0; iCycle<iCount; iCycle++)
	//{
	//	iArea = iArea + (test[iCycle].x*test[(iCycle + 1) % iCount].y - test[(iCycle + 1) % iCount].x*test[iCycle].y);
	//}
	//area = 0.5f*iArea;
	//CCLOG("%f,area  zzzzzzzzzz ", area);
	//
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_staticBody;

	////bodyDef.position = position;
	////	bodyDef.position = origin_body->GetUserData();
	////bodyDef.angle = origin_body->GetAngle();
	//bodyDef.position.Set(ptm(100), ptm(100));
	//b2FixtureDef fixtureDef;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.0f;
	//fixtureDef.restitution = 0.0f;
	////	fixtureDef.filter= origFixture->GetFilterData();
	//b2PolygonShape polyShape;
	//b2Body* body = NULL;
	//b2Vec2 *points = new b2Vec2[test.size()];
	//for (int i = 0; i < test.size(); i++)
	//{
	//	points[i] = test[i];
	//}
	//polyShape.Set(points, test.size());
	//fixtureDef.shape = &polyShape;
	//body = m_world->CreateBody(&bodyDef);
	//body->CreateFixture(&fixtureDef);


	//auto s = ShatterSprite::create(body, m_brickLayer->getBricks().at(5));
	//this->addChild(s);
	////s->getB2Body()->SetType(b2_dynamicBody);
	//s->setPosition(Point(150, 150));
	////CCLOG("%f,%f,texture _rect .origin.x,.y", p.x, p.y);
	////CCLOG("%f,%f,texture _rect .this->_rect.size.w,.h", this->_rect.size.width, this->_rect.size.height);
	//CCLOG("%f,%f,s->getTextureRect().origin.x,.y", s->getTextureRect().origin.x, s->getTextureRect().origin.y);

	//auto s1 = Sprite::createWithSpriteFrame(m_brickLayer->getBricks().at(5)->getSpriteFrame());
	//this->addChild(s1);
	//s1->setPosition(200, 200);
	//CCLOG("%f,%f,s1->getTextureRect().origin.x,.y", s1->getTextureRect().origin.x, s1->getTextureRect().origin.y);
	
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
	//m_worldAABB = new b2AABB();
	//m_worldAABB->lowerBound.Set(0, 0);
	//m_worldAABB->upperBound.Set(ptm(visibleSize.width), ptm(visibleSize.height));
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
	//flags += b2Draw::e_aabbBit;  //AABB块  
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
	this->dealContact();
	//this->destroyOutsideBodies();
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
		//CCLOG("contact type  %d.!", collideType);
		switch (collideType)
		{
		case COLLIDE_TYPE::BALL_BRICK:
		{
			//CCLOG("contact!");
			auto brick = (GameBrick*)(contact.getBrickFixture()->GetBody()->GetUserData());
			b2Vec2 point = contact.getContactPoint();
			undealCollideBrick[brick] = point;
			//CCLOG("contact! point %f.%f", mtp(point.x), mtp(point.y));
			//brick->collision(point);		
			/*			auto label = Label::createWithTTF("contact", "arial.ttf", 40);
			label->setColor(Color3B(255, 0, 0));
			label->setPosition(Point(mtp(point.x),mtp(point.y)));
			this->addChild(label);
			label->runAction(FadeOut::create(1.0f));*/
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

	for (auto collide_brick : undealCollideBrick)
	{
		auto brick = collide_brick.first;
		auto point = collide_brick.second;
		int brick_hp = brick->collision(point);
		if (brick_hp <= 0)
		{
			brickBomb(brick, point);
		}
	}

	undealCollideBrick.clear();

}
void GameWorld::destroyOutsideBodies()
{
	//AABBQuery query;
	//b2AABB aabb;
	std::vector<b2Body*> outBodies;
	//aabb.lowerBound.Set(0, 0);
	//aabb.upperBound.Set(ptm(visibleSize.width), ptm(visibleSize.height));
	//m_world->QueryAABB(&query, aabb);
	//std::vector<b2Body*> inBodies = query.getInScreenBodies();
	for (b2Body* body = m_world->GetBodyList(); body; body = body->GetNext())
	{
		//std::vector<b2Body*>::iterator it_targetBody;
		//it_targetBody = std::find(inBodies.begin(), inBodies.end(), body);
		b2Vec2 position = body->GetPosition();
		if (position.y < -1 || position.x < -1 || position.x > ptm(visibleSize.width))
		{
			outBodies.push_back(body);
		}
	
	}

	for (auto body : outBodies)
	{
		PhysicsSprite* sprite = (PhysicsSprite*)body->GetUserData();
		if (sprite)
			sprite->removeFromParentAndCleanup(true);
		body->SetUserData(nullptr);

		m_world->DestroyBody(body);
		body = nullptr;
		
	
	}
	
	//outBodies.clear();
}