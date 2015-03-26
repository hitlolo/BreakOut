#include "PhysicsSprite.h"

PhysicsSprite::PhysicsSprite()
: _ignoreBodyRotation(false)
, _pB2Body(nullptr)
, _PTMRatio(PTM_RATIO)
{}

PhysicsSprite* PhysicsSprite::create()
{
	PhysicsSprite* pRef = new (std::nothrow) PhysicsSprite();
	if (pRef && pRef->init())
	{
		pRef->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRef);
	}
	return pRef;
}


PhysicsSprite* PhysicsSprite::createWithTexture(Texture2D *pTexture)
{
	PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
	if (pRet && pRet->initWithTexture(pTexture))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

PhysicsSprite* PhysicsSprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
	PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
	if (pRet && pRet->initWithTexture(pTexture, rect))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

PhysicsSprite* PhysicsSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
	PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
	if (pRet && pRet->initWithSpriteFrame(pSpriteFrame))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

PhysicsSprite* PhysicsSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
	if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

PhysicsSprite* PhysicsSprite::create(const char *pszFileName)
{
	PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
	if (pRet && pRet->initWithFile(pszFileName))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

PhysicsSprite* PhysicsSprite::create(const char *pszFileName, const Rect& rect)
{
	PhysicsSprite* pRet = new (std::nothrow) PhysicsSprite();
	if (pRet && pRet->initWithFile(pszFileName, rect))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then getNodeToParentTransform won't be called.
bool PhysicsSprite::isDirty() const
{
	return true;
}

bool PhysicsSprite::isIgnoreBodyRotation() const
{
	return _ignoreBodyRotation;
}

void PhysicsSprite::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
	_ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Vec2& PhysicsSprite::getPosition() const
{
	return getPosFromPhysics();
}

void PhysicsSprite::getPosition(float* x, float* y) const
{
	if (x == nullptr || y == nullptr) {
		return;
	}
	const Vec2& pos = getPosFromPhysics();
	*x = pos.x;
	*y = pos.y;
}


float PhysicsSprite::getPositionX() const
{
	return getPosFromPhysics().x;
}

float PhysicsSprite::getPositionY() const
{
	return getPosFromPhysics().y;
}

b2Body* PhysicsSprite::getB2Body() const
{
#if CC_ENABLE_BOX2D_INTEGRATION
	return _pB2Body;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
	return nullptr;
#endif
}

void PhysicsSprite::setB2Body(b2Body *pBody)
{
#if CC_ENABLE_BOX2D_INTEGRATION
	_pB2Body = pBody;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
#endif
}

float PhysicsSprite::getPTMRatio() const
{
#if CC_ENABLE_BOX2D_INTEGRATION
	return _PTMRatio;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
	return 0;
#endif
}

void PhysicsSprite::setPTMRatio(float fRatio)
{
#if CC_ENABLE_BOX2D_INTEGRATION
	_PTMRatio = fRatio;
#else
	CCASSERT(false, "Can't call box2d methods when Box2d is disabled");
#endif
}


const Vec2& PhysicsSprite::getPosFromPhysics() const
{
	static Vec2 s_physicPosion;

#if CC_ENABLE_BOX2D_INTEGRATION

	b2Vec2 pos = _pB2Body->GetPosition();
	float x = pos.x * _PTMRatio;
	float y = pos.y * _PTMRatio;
	s_physicPosion = Vec2(x, y);
#endif
	return s_physicPosion;
}

void PhysicsSprite::setPosition(const Vec2 &pos)
{

#if CC_ENABLE_BOX2D_INTEGRATION

	float angle = _pB2Body->GetAngle();
	_pB2Body->SetTransform(b2Vec2(pos.x / _PTMRatio, pos.y / _PTMRatio), angle);
	Sprite::setPosition(pos);
	//SET_DIRTY_RECURSIVELY();
#endif

}

float PhysicsSprite::getRotation() const
{

#if CC_ENABLE_BOX2D_INTEGRATION

	return (_ignoreBodyRotation ? Sprite::getRotation() :
		CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
#else
	return 0.0f;
#endif

}

void PhysicsSprite::setRotation(float fRotation)
{
	if (_ignoreBodyRotation)
	{
		Sprite::setRotation(fRotation);
	}

#if CC_ENABLE_BOX2D_INTEGRATION
	else
	{
		b2Vec2 p = _pB2Body->GetPosition();
		float radians = CC_DEGREES_TO_RADIANS(fRotation);
		_pB2Body->SetTransform(p, radians);
	}
#endif

}

void PhysicsSprite::syncPhysicsTransform() const
{
	// Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990

#if CC_ENABLE_BOX2D_INTEGRATION

	b2Vec2 pos = _pB2Body->GetPosition();

	float x = pos.x * _PTMRatio;
	float y = pos.y * _PTMRatio;

	if (_ignoreAnchorPointForPosition)
	{
		x += _anchorPointInPoints.x;
		y += _anchorPointInPoints.y;
	}

	// Make matrix
	float radians = _pB2Body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);

	if (!_anchorPointInPoints.equals(Vec2::ZERO))
	{
		x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
		y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
	}

	// Rot, Translate Matrix

	float mat[] = { (float)c * _scaleX, (float)s * _scaleX, 0, 0,
		(float)-s * _scaleY, (float)c * _scaleY, 0, 0,
		0, 0, 1, 0,
		x, y, 0, 1 };

	_transform.set(mat);
#endif
}

const Mat4& PhysicsSprite::getNodeToParentTransform() const
{
	syncPhysicsTransform();

	return _transform;
}

void PhysicsSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (isDirty())
	{
		syncPhysicsTransform();
	}

	Sprite::draw(renderer, _transform, flags);

}
