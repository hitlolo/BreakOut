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
	createPhysicsWorld();
	createEdgeBox();
	initLevelData(level);
		
	return true;
	

}

bool GameWorld::initLevelData(int level)
{

	return true;
}


GameWorld::GameWorld()
: _world(nullptr)
, _debugDraw(nullptr)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	originPoint = Director::getInstance()->getVisibleOrigin();
}

GameWorld::~GameWorld()
{

	CC_SAFE_DELETE(_world);
	CC_SAFE_DELETE(_debugDraw);
}

void GameWorld::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void GameWorld::addBackground()
{
	auto background = Scale9Sprite::createWithSpriteFrameName("res/menuPanel.png");
	background->setContentSize(Size(288, 512));
	background->setPosition(CENTER);
	this->addChild(background);

}

void GameWorld::createPhysicsWorld()
{
	//1.gravity
	b2Vec2 gravity = b2Vec2(0.0f, -0.5f);
	_world = new b2World(gravity);

	
	//2.debug
#if 1
	_debugDraw = new GLESDebugDraw(PTM_RATIO);   //这里新建一个 debug渲染模块  
	_world->SetDebugDraw(_debugDraw);    //设置  
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//b2Draw::e_centerOfMassBit;   //获取需要显示debugdraw的块  
	//b2Draw::e_aabbBit;  //AABB块  
	//b2Draw::e_centerOfMassBit; 物体质心  
	//b2Draw::e_jointBit;  //关节  
	//b2Draw::e_shapeBit;   形状  
	_debugDraw->SetFlags(flags);   //需要显示那些东西  
#endif

	
}

void GameWorld::createEdgeBox()
{
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//wall definitions
	//BOTTOM
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(visibleSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);
	// top
	groundEdge.Set(b2Vec2(0, visibleSize.height / PTM_RATIO), b2Vec2(visibleSize.width / PTM_RATIO, visibleSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// left
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, visibleSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// right
	groundEdge.Set(b2Vec2(visibleSize.width / PTM_RATIO, 0), b2Vec2(visibleSize.width / PTM_RATIO, visibleSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);


	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position.Set(144 / PTM_RATIO, 256 / PTM_RATIO);
	auto body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 12.0 / PTM_RATIO;

	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 0.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	body->CreateFixture(&ballShapeDef);
	
	//auto ball = Sprite::create("ball-hd.png");
	//ball->setPosition(100, 300);
	//this->addChild(ball);
	//body->SetUserData(ball);
}

#if 1
void GameWorld::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

	kmGLPushMatrix();
	_world->DrawDebugData();

	kmGLPopMatrix();

	CHECK_GL_ERROR_DEBUG();
}
#endif

void GameWorld::update(float dt)
{
	_world->Step(dt, 10, 10);
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			Sprite *ballData = (Sprite *)b->GetUserData();
			ballData->setPosition(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO);
			ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}