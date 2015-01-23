#include "test.h"

Scene* test::createScene()
{
	auto scene = Scene::create();
	auto layer = test::create();
	scene->addChild(layer);
	return scene;
}

bool test::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initPhysics();
	this->scheduleUpdate();
	return true;
}

void test::initPhysics()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//this->_ball = Sprite::create("ball-hd.png");
	//_ball->setPosition(100, 300);
	//this->addChild(_ball);

	b2Vec2 gravity = b2Vec2(0, -10.0f);
	_world = new b2World(gravity);
	debugDraw = new GLESDebugDraw(PTM_RATIO);   //这里新建一个 debug渲染模块  
	_world->SetDebugDraw(debugDraw);    //设置  
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//b2Draw::e_centerOfMassBit;   //获取需要显示debugdraw的块  
	//b2Draw::e_aabbBit;  //AABB块  
	//b2Draw::e_centerOfMassBit; 物体质心  
	//b2Draw::e_jointBit;  //关节  
	//b2Draw::e_shapeBit;   形状  
	debugDraw->SetFlags(flags);   //需要显示那些东西  

	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position.Set(100 / PTM_RATIO, 300 / PTM_RATIO);
	//bodyDef.userData = _ball;
	_body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 52.0 / PTM_RATIO;

	b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	_body->CreateFixture(&ballShapeDef);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 2);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//wall definitions
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(visibleSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

}

test::~test()
{
	CC_SAFE_DELETE(_world);
	CC_SAFE_DELETE(debugDraw);
}

void test::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it
	//
	Layer::draw(renderer, transform, flags);


	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

	kmGLPushMatrix();

	_world->DrawDebugData();

	kmGLPopMatrix();

	CHECK_GL_ERROR_DEBUG();

}

void test::update(float dt)
{
	_world->Step(dt, 10, 10);
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) 
	{
		if (b->GetUserData() != NULL) {
			Sprite *ballData = (Sprite *)b->GetUserData();
			ballData->setPosition(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO);
			ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}