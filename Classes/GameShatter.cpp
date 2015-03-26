#include "GameShatter.h"

GameShatter* GameShatter::create(GameBrick* target, b2Vec2 point)
{

	GameShatter * ret = new (std::nothrow) GameShatter(target,point);
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

GameShatter::GameShatter(GameBrick* target, b2Vec2 point)
	:m_cut(5)
	, m_RayFixture(nullptr)
{
	m_target = target;
	m_targetBody = target->getB2Body();
	m_world = target->getB2Body()->GetWorld();
	m_collidePoint = point;
}

GameShatter::~GameShatter()
{

}

bool GameShatter::init()
{
	if (!Node::init())
	{
		return  false;
	}
	Point position = m_target->getPosition();
	this->setPosition(position);
	Size  size = m_target->getContentSize();
	this->setContentSize(size);
	m_collidePoint = resetOffset(m_collidePoint);

	this->bomb();
	return true;
}

b2Vec2 GameShatter::resetOffset(b2Vec2 point)
{
	Vec2 originLocation = m_target->getOriginLocation();
	Vec2 contactLocation = Vec2(mtp(point.x), mtp(point.y));
	if (contactLocation.y < originLocation.y)
	{
		
		if (contactLocation.y < originLocation.y - getContentSize().height / 2)
		{
			contactLocation.y = originLocation.y - getContentSize().height / 2;
			return b2Vec2(ptm(contactLocation.x), ptm(contactLocation.y));
		}
		return b2Vec2(ptm(contactLocation.x), ptm(contactLocation.y));
	}
	else 
	{
		if (contactLocation.y > originLocation.y + getContentSize().height / 2)
		{
			contactLocation.y = originLocation.y + getContentSize().height / 2;
			return b2Vec2(ptm(contactLocation.x), ptm(contactLocation.y));
		}
		return b2Vec2(ptm(contactLocation.x), ptm(contactLocation.y));
	}


}

float32 GameShatter::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	
	m_RayFixture = fixture;
	m_RayPoint = resetOffset(point);
	m_RayNormal = normal;
	m_RayFraction = fraction;
	auto body = fixture->GetBody();
	
	
	

	std::vector<b2Body*>::iterator iter = std::find(targetBody_vector.begin(), targetBody_vector.end(), body);
	if (iter != targetBody_vector.end())
	{
		Vec2 contact_point = Vec2(Vec2(mtp(m_RayPoint.x), mtp(m_RayPoint.y)));
		Vec2 locate_point = this->getPosition();
		Vec2 draw_point = contact_point - locate_point;
		//	start -= locate_point;
		//	end -= locate_point;
		//	CCLOG("%f,%f,start", start.x, start.y);
		//	CCLOG("%f,%f,end", end.x, end.y);

		m_draw->drawCircle(draw_point, 3.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	}
		//CCLOG(" find !!!!!!!!!!!");
	else 
		CCLOG("can not find value body");
//	CCLOG("%f,brick~~~~~~~~~~~~~~", m_RayFraction);
	return 1;
}


void GameShatter::bomb()
{
	Vec2 contact_point = Vec2(Vec2(mtp(m_collidePoint.x), mtp(m_collidePoint.y)));
	Vec2 locate_point = this->getPosition();
	Vec2 draw_point = contact_point - locate_point;
	//draw_point.x += this->getContentSize().width / 2;
	//draw_point.y += this->getContentSize().height / 2;
	//Vec2 draw_point = Vec2(point.x,point.y);
	CCLOG("%f,%f,contact_point", contact_point.x, contact_point.y);
	CCLOG("%f,%f,locate_point", locate_point.x, locate_point.y);
	CCLOG("%f,%f,draw_point", draw_point.x, draw_point.y);

	m_draw = DrawNode::create();
	//	m_draw->setAnchorPoint(Point(1, 1));
	this->addChild(m_draw);
	//m_draw->drawCircle(draw_point, 3.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));


	targetBody_vector.push_back(this->m_targetBody);

	float cutAngle = 0.0;
	b2Vec2 p1, p2;

	for (int i = 0; i < m_cut; i++)
	{
		//float angle = getRandomAngle();
		//float y = mtp(m_collidePoint.y) + 100;
		//float y1 = mtp(m_collidePoint.y) - 100;
		//float x = (y - mtp(m_collidePoint.y) + tan(CC_DEGREES_TO_RADIANS(angle))*mtp(m_collidePoint.x)) / tan(CC_DEGREES_TO_RADIANS(angle));
		//float x1 = (y1 - mtp(m_collidePoint.y) + tan(CC_DEGREES_TO_RADIANS(angle))*mtp(m_collidePoint.x)) / tan(CC_DEGREES_TO_RADIANS(angle));
		cutAngle = CC_DEGREES_TO_RADIANS(getRandomAngle());
		//p1.x = (contact_point.x + i / 10.0 - 100 * cos(cutAngle));
		//p1.y = (contact_point.y - 100 * sin(cutAngle)) ;
		//p2.x = (contact_point.x + 100 * cos(cutAngle)) ;
		//p2.y = (contact_point.y + 100 * sin(cutAngle));

		p1.y = mtp(m_collidePoint.y) + 50;
		p2.y = mtp(m_collidePoint.y) - 50;
		p1.x = (p1.y - mtp(m_collidePoint.y) + tan(cutAngle)*mtp(m_collidePoint.x)) / tan(cutAngle);
		p2.x = (p2.y - mtp(m_collidePoint.y) + tan(cutAngle)*mtp(m_collidePoint.x)) / tan(cutAngle);
		
		Vec2 start = Vec2(p1.x, p1.y);
		Vec2 end   = Vec2(p2.x, p2.y);
		Vec2 locate_point = this->getPosition();
	//	start -= locate_point;
	//	end -= locate_point;
	//	CCLOG("%f,%f,start", start.x, start.y);
	//	CCLOG("%f,%f,end", end.x, end.y);
		
		m_draw->drawLine(start - locate_point, end - locate_point, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
	//	m_draw->drawLine(end -= locate_point, start -= locate_point, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
		m_world->RayCast(this, b2Vec2(ptm(start.x), ptm(start.y)), b2Vec2(ptm(end.x), ptm(end.y)));
		m_world->RayCast(this, b2Vec2(ptm(end.x), ptm(end.y)), b2Vec2(ptm(start.x), ptm(start.y)));
	
	}

}

float GameShatter::getRandomAngle()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
//	mt = new mt19937(randomDevice());
	uniform_real_distribution<float> dist(0.0f, 180.0f);
	float angle = dist(mt);
	if (angle != 90.0f)
	{
		return angle;
	}
	else

	{
		uniform_real_distribution<float> dist(91.0f, 180.0f);
		return  dist(mt);
	}
	
}