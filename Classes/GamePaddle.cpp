#include "GamePaddle.h"

GamePaddle::GamePaddle(b2World* world, b2Body* ground)
: m_mouseJoint(nullptr)
, _ignoreBodyRotation(false)
, m_world(world)
, m_groundBody(ground)
, m_type(BAR::NORMAL)
, m_melody(MELODY::XI)
{
	
}

GamePaddle::~GamePaddle()
{

}

GamePaddle* GamePaddle::create(b2World* world, b2Body* ground)
{
	GamePaddle * ret = new (std::nothrow) GamePaddle(world, ground);
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

bool GamePaddle::init()
{
	if (!Scale9Sprite::init())
	{
		return false;
	}
	initSelfImage();
	initPhysicsAttributes();
	scheduleUpdate();
	return true;
}


void  GamePaddle::initSelfImage()
{
	this->initWithSpriteFrameName(selectRandomFile());
	this->setContentSize(NORMAL_SIZE);
	
}

std::string  GamePaddle::selectRandomFile()
{
	srand((unsigned)time(NULL));
	int color = ((int)rand()) % 6;
	color += 4;
	String* file = String::createWithFormat("Bar%d.png", color);
	return file->getCString(); 
}

void GamePaddle::addFixturesToBody(b2Body* body)
{
	auto fixture = body->GetFixtureList(); 
	if (fixture)
	{
		body->DestroyFixture(fixture);

	}
	std::string type_name;
	switch (m_type)
	{
		case BAR::NORMAL:
				type_name = "bar_normal";
				break;
		case BAR::SHORT:
				type_name = "bar_short";
				break;
		case BAR::LONG:
				type_name = "bar_long";
				break;
	}

	GB2ShapeCache::getInstancs()->addFixturesToBody(body, type_name);
}


void GamePaddle::initPhysicsAttributes()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType::b2_dynamicBody;
	bodyDef.position.Set(ptm(288), ptm(64));
	bodyDef.gravityScale = 0.0f;
	bodyDef.userData = this; 
	bodyDef.awake = true;
//	bodyDef.position.Set(ptm(88), ptm(32));
	m_body = m_world->CreateBody(&bodyDef);

	
	this->setB2Body(m_body);
	this->setPTMRatio(PTM_RATIO);	this->addFixturesToBody(m_body);
	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	jointDef.collideConnected = true;
	jointDef.Initialize(getB2Body(), m_groundBody, getB2Body()->GetWorldCenter(), worldAxis);
	getB2Body()->GetWorld()->CreateJoint(&jointDef);
	
}


void GamePaddle::onBeginMove(const b2Vec2 position)
{
	if (m_mouseJoint != NULL) return;
	

	else
	{
		b2MouseJointDef mouseJointDef;
		mouseJointDef.bodyA = m_groundBody;
		mouseJointDef.bodyB = getB2Body();
		mouseJointDef.target = position;
		mouseJointDef.collideConnected = true;
		mouseJointDef.maxForce = 1000.0f * getB2Body()->GetMass();

		m_mouseJoint = (b2MouseJoint *)getB2Body()->GetWorld()->CreateJoint(&mouseJointDef);
	}

	
//	getB2Body()->SetAwake(true);
			
		
	
}

void GamePaddle::onMove(const std::vector<Touch*>& touches)
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
void GamePaddle::onMoveEnd()
{
	//if (m_mouseJoint) 
	//{
	//	getB2Body()->GetWorld()->DestroyJoint(m_mouseJoint);
	//	m_mouseJoint = NULL;
	//}
}
void GamePaddle::onMoveCancel()
{
	/*if (m_mouseJoint)
	{
		getB2Body()->GetWorld()->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
	}*/
}


bool GamePaddle::isDirty() const
{
	return true;
}

bool GamePaddle::isIgnoreBodyRotation() const
{
	return _ignoreBodyRotation;
}

void GamePaddle::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
	_ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Vec2& GamePaddle::getPosition() const
{
	return getPosFromPhysics();
}

void GamePaddle::getPosition(float* x, float* y) const
{
	if (x == nullptr || y == nullptr) {
		return;
	}
	const Vec2& pos = getPosFromPhysics();
	*x = pos.x;
	*y = pos.y;
}


float GamePaddle::getPositionX() const
{
	return getPosFromPhysics().x;
}

float GamePaddle::getPositionY() const
{
	return getPosFromPhysics().y;
}

b2Body* GamePaddle::getB2Body() const
{
#if CC_ENABLE_BOX2D_INTEGRATION
	return m_body;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
	return nullptr;
#endif
}

void GamePaddle::setB2Body(b2Body *pBody)
{
#if CC_ENABLE_BOX2D_INTEGRATION
	m_body = pBody;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
#endif
}

float GamePaddle::getPTMRatio() const
{
#if CC_ENABLE_BOX2D_INTEGRATION
	return m_ptm;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
	return 0;
#endif
}

void GamePaddle::setPTMRatio(float fRatio)
{
#if CC_ENABLE_BOX2D_INTEGRATION
	m_ptm = fRatio;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
#endif
}


const Vec2& GamePaddle::getPosFromPhysics() const
{
	static Vec2 s_physicPosion;

#if CC_ENABLE_BOX2D_INTEGRATION

	b2Vec2 pos = m_body->GetPosition();
	float x = pos.x * m_ptm;
	float y = pos.y * m_ptm;
	s_physicPosion = Vec2(x, y);
#endif
	return s_physicPosion;
}

void GamePaddle::setPosition(const Vec2 &pos)
{

#if CC_ENABLE_BOX2D_INTEGRATION

	float angle = m_body->GetAngle();
	m_body->SetTransform(b2Vec2(pos.x / m_ptm, pos.y / m_ptm), angle);
#endif
	//add
	Scale9Sprite::setPosition(pos);
}

float GamePaddle::getRotation() const
{

#if CC_ENABLE_BOX2D_INTEGRATION

	return (_ignoreBodyRotation ? Scale9Sprite::getRotation() :
		CC_RADIANS_TO_DEGREES(m_body->GetAngle()));
#else
	return 0.0f;
#endif

}

void GamePaddle::setRotation(float fRotation)
{
	if (_ignoreBodyRotation)
	{
		Scale9Sprite::setRotation(fRotation);
	}

#if CC_ENABLE_BOX2D_INTEGRATION
	else
	{
		b2Vec2 p = m_body->GetPosition();
		float radians = CC_DEGREES_TO_RADIANS(fRotation);
		m_body->SetTransform(p, radians);
	}
#endif

}

void GamePaddle::syncPhysicsTransform() const
{
	// Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990

#if CC_ENABLE_BOX2D_INTEGRATION

	b2Vec2 pos = m_body->GetPosition();

	float x = pos.x * m_ptm;
	float y = pos.y * m_ptm;

	if (_ignoreAnchorPointForPosition)
	{
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

	// Make matrix
	float radians = m_body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);

	if (!_anchorPointInPoints.equals(Vec2::ZERO))
	{
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}

	// Rot, Translate Matrix

	float mat[] = 
	{ (float)c * _scaleX, (float)s * _scaleX, 0, 0,
		(float)-s * _scaleY, (float)c * _scaleY, 0, 0,
		0, 0, 1, 0,
		x, y, 0, 1 };

	_transform.set(mat);
#endif
}

const Mat4& GamePaddle::getNodeToParentTransform() const
{
	syncPhysicsTransform();

	return _transform;
}

//void GamePaddle::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
//{
//
//		if (isDirty())
//		{
//			syncPhysicsTransform();
//			
//		}
//		_transform = _transform*parentTransform;
//		Scale9Sprite::visit(renderer, _transform, parentFlags);
//}

void GamePaddle::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (isDirty())
	{
		syncPhysicsTransform();
		
	}
	Scale9Sprite::draw(renderer, _transform, flags);
}


void GamePaddle::update(float time) 
{
	this->setPosition(Vec2((getB2Body()->GetPosition().x) * PTM_RATIO,getB2Body()->GetPosition().y * PTM_RATIO));

}