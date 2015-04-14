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
	:m_cut(3), m_left(0.0f), m_right(0.0f), m_up(0.0f), m_bottom(0.0f)
	, m_RayFixture(nullptr)
	, m_explosionRadius(30.0f)
{
	
	m_target = target;
	m_targetBody = target->getB2Body();
	m_targetLocation = target->getOriginLocation();
	m_originTexture = target->getTexture();
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


	m_draw = DrawNode::create();
	this->addChild(m_draw);

	Point position = m_target->getPosition();
	this->setPosition(position);

	Size  size = m_target->getContentSize();
	this->setContentSize(size);

	this->initBoundary();
	this->m_exploPoint = m_targetBody->GetWorldPoint(getExploPoint());

	//check whether the contact point is on the body
	//if not
	//reset it
	if (!pointInBody(m_collidePoint))
	{
		this->resetOffset(m_collidePoint);
	}
	
	return true;
}

void GameShatter::initBoundary()
{
	m_left = -ptm(this->getContentSize().width)* 0.5f;
	m_right = ptm(this->getContentSize().width)* 0.5f;

	m_up = ptm(this->getContentSize().height) * 0.5f;
	m_bottom = -ptm(this->getContentSize().height) * 0.5f;

}

b2Vec2 GameShatter::getExploPoint()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_real_distribution<float> dist_x(m_left + 0.2f, m_right-0.2f);
	float x = dist_x(mt);
	uniform_real_distribution<float> dist_y(m_bottom + 0.2f, m_up - 0.2f);
	float y = dist_y(mt);
	
	return b2Vec2(x, y);
}

void GameShatter::resetOffsetX(b2Vec2& point)
{
	
	point = m_targetBody->GetLocalPoint(point);	
	if (point.x < m_left)
	{
		point.x = m_left;
	}
	else if (point.x > m_right)
	{
		point.x = m_right;
	}
	
	point = m_targetBody->GetWorldPoint(point);
	
}

void GameShatter::resetOffsetY(b2Vec2& point)
{

	point = m_targetBody->GetLocalPoint(point);
	if (point.y < m_bottom)
	{
		point.y = m_bottom;
	}
	else if (point.y > m_up)
	{
		point.y = m_up;
	}

	point = m_targetBody->GetWorldPoint(point);
}

void GameShatter::resetOffset(b2Vec2& point)
{	
	this->resetOffsetX(point);
	this->resetOffsetY(point);	
}

float GameShatter::getRandomAngle()
{
	using namespace std;
	random_device randomDevice;
	mt19937      mt(randomDevice());
	uniform_real_distribution<float> dist(5.0f, 170.0f);
	float angle;
	do
	{		
		angle = dist(mt);
	} while (!checkSliceAngle(angle) || angle == 90.0f);

	return angle;

}

bool  GameShatter::checkSliceAngle(float angle)
{
	if (sliceAngle_vector.size() == 0)
	{
		return true;
	}
	
	for (auto pushed_angle : sliceAngle_vector)
	{
		if (pushed_angle > angle)
		{
			if (pushed_angle - angle < 20.0f)
			{
				return false;
			}
			else
				return true;
		}
		else if (pushed_angle < angle)
		{
			if (angle - pushed_angle < 20.0f)
			{
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}


}


void GameShatter::bomb()
{
	//Vec2 contact_point = Vec2(Vec2(mtp(m_collidePoint.x), mtp(m_collidePoint.y)));
	//Vec2 locate_point = this->getPosition();
	//Vec2 draw_point = contact_point - locate_point;


	//m_draw->drawCircle(draw_point, 3.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(1, 1, 1, 1));

	//Vec2 contact_point = Vec2(Vec2(mtp(m_exploPoint.x), mtp(m_exploPoint.y)));
	//Vec2 locate_point = this->getPosition();
	//Vec2 draw_point = contact_point - locate_point;
	//m_draw->drawCircle(draw_point, 3.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(1,0,0, 1));


	//start boom
	targetBody_vector.push_back(this->m_targetBody);

	float sliceAngle = 0.0;
	b2Vec2 p1, p2;
	for (int i = 0; i < m_cut; i++)
	{
		sliceAngle = getRandomAngle();
		sliceAngle_vector.push_back(sliceAngle);		
	}

	for (auto sliceAngle : sliceAngle_vector)
	{
	
		sliceAngle = CC_DEGREES_TO_RADIANS(sliceAngle);
		p1.x = (mtp(m_exploPoint.x) - 100 * cos(sliceAngle));
		p1.y = (mtp(m_exploPoint.y) - 100 * sin(sliceAngle));
		p2.x = (mtp(m_exploPoint.x) + 100 * cos(sliceAngle));
		p2.y = (mtp(m_exploPoint.y) + 100 * sin(sliceAngle));

		//点斜式
		//p1.y = mtp(m_collidePoint.y) + 50;
		//p2.y = mtp(m_collidePoint.y) - 50;
		//p1.x = (p1.y - mtp(m_collidePoint.y) + tan(cutAngle)*mtp(m_collidePoint.x)) / tan(cutAngle);
		//p2.x = (p2.y - mtp(m_collidePoint.y) + tan(cutAngle)*mtp(m_collidePoint.x)) / tan(cutAngle);
		
		Vec2 start = Vec2(p1.x, p1.y);
		Vec2 end   = Vec2(p2.x, p2.y);
#if 0
		Vec2 locate_point = this->getPosition();

		m_draw->drawLine(start - locate_point, end - locate_point, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
		m_draw->drawLine(end -= locate_point, start -= locate_point, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
#endif
	
		m_world->RayCast(this, b2Vec2(ptm(start.x), ptm(start.y)), b2Vec2(ptm(end.x), ptm(end.y)));
		m_world->RayCast(this, b2Vec2(ptm(end.x), ptm(end.y)), b2Vec2(ptm(start.x), ptm(start.y)));
	
	}

	this->createNewBodyAndNewSprite();
	this->cleanOldBodyAndSprite();
	//after bomb ,do self release
	this->removeFromParentAndCleanup(true);
}

float32 GameShatter::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	
	m_RayFixture = fixture;         //intersection fixture	
	m_RayPoint = point;             //intersection point
	m_RayNormal = normal;
	m_RayFraction = fraction;
	auto body = fixture->GetBody(); //intersection body

	if (!pointInBody(m_RayPoint))
	{
		resetOffset(m_RayPoint);
	}

	std::vector<b2Body*>::iterator it_targetBody;
	it_targetBody = std::find(targetBody_vector.begin(), targetBody_vector.end(), body);
	if (it_targetBody != targetBody_vector.end())
	{

		std::map<b2Body*, b2Vec2>::iterator it_m = targetBody_map.find(body);
		if (it_m != targetBody_map.end())
		{
			//find		
			//body ,start point ,end  point
			this->splitBrick(it_m->first, it_m->second, m_RayPoint);
		}
		else
		{
			targetBody_map[body] = m_RayPoint;

		}
	}
	return -1;
}



void  GameShatter::splitBrick(b2Body* body, b2Vec2& start, b2Vec2& end)
{
	//check whether the start point and end point are the same or too close
	if (start == end)
		return;
	else
	{
		b2Vec2 lenght = start - end;
		float32 len = lenght.Length();
		if (len < 0.000050f)
			return;
	}
	//if not....

	b2Fixture* origFixture = body->GetFixtureList();
	b2PolygonShape* poly = (b2PolygonShape*)origFixture->GetShape();

	std::vector<b2Vec2> shapeAVertices;
	std::vector<b2Vec2> shapeBVertices;

	b2Vec2 interPointA = body->GetLocalPoint(start);
	b2Vec2 interPointB = body->GetLocalPoint(end);

	shapeAVertices.push_back(interPointA);
	shapeAVertices.push_back(interPointB);
	shapeBVertices.push_back(interPointA);
	shapeBVertices.push_back(interPointB);

	// I iterate over all vertices of the original body. ;
	// I use the function det() ("det" stands for "determinant") to see on which side of AB each point is standing on. The parameters it needs are the coordinates of 3 points:
	// - if it returns a value >0, then the three points are in clockwise order (the point is under AB)
	// - if it returns a value =0, then the three points lie on the same line (the point is on AB)
	// - if it returns a value <0, then the three points are in counter-clockwise order (the point is above AB). 
	float d;
	int numVertices = poly->GetVertexCount();
	for (int i = 0; i < numVertices; i++)
	{
		b2Vec2 v = poly->GetVertex(i);
		//resetOffset(v);
		if (v == interPointA || v == interPointB)
			continue;
		d = det(interPointA.x, interPointA.y, interPointB.x, interPointB.y, v.x, v.y);
		if (d > 0)
		{
			shapeAVertices.push_back(v);
		}
		else
		{
			shapeBVertices.push_back(v);
		}
	}

	// In order to be able to create the two new shapes, I need to have the vertices arranged in clockwise order.
	// I call my custom method, arrangeClockwise(), which takes as a parameter a vector, representing the coordinates of the shape's vertices and returns a new vector, with the same points arranged clockwise.
	ClockwiseSortPoints(shapeAVertices);
	ClockwiseSortPoints(shapeBVertices);

	float areaA = getArea(shapeAVertices);
	float areaB = getArea(shapeBVertices);

	bool is_created = false;

	if (areaA >= 0.02)
	{
		is_created = createShatter(body, shapeAVertices);
	}

#if 0
	if (is_created == false)

	{
		for (int i = 0; i < shapeAVertices.size(); i++)
		{
			b2Vec2 point = b2Vec2(shapeAVertices[i].x, shapeAVertices[i].y);
			//contact_point
			point = body->GetWorldPoint(point);
			Vec2 contact_point = Vec2(Vec2(mtp(point.x), mtp(point.y)));
			Vec2 locate_point = this->getPosition();
			Vec2 draw_point = contact_point - locate_point;
			//	start -= locate_point;
			//	end -= locate_point;
			//	CCLOG("%f,%f,start", start.x, start.y);
			//	CCLOG("%f,%f,end", end.x, end.y);
			m_draw->drawCircle(draw_point, 1.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(1, 0, 0, 1));
			//	auto s = String::createWithFormat("%d", i);
			//auto label = Label::createWithTTF(s->getCString(), "arial.ttf", 20);

			CCLOG("%f,%f,%d !area:%f!!!!AAAAAAAA!!!fail!!!!!!", shapeAVertices[i].x, shapeAVertices[i].y, i, areaA);
		}
	}

#endif
	// creating the second shape, if big enough  

	if (areaB >= 0.02 )
	{
		is_created = createShatter(body, shapeBVertices);
	}

#if 0
	if (is_created == false)

	{
		for (int i = 0; i < shapeBVertices.size(); i++)
		{
			b2Vec2 point = b2Vec2(shapeBVertices[i].x, shapeBVertices[i].y);
			//contact_point
			point = body->GetWorldPoint(point);
			Vec2 contact_point = Vec2(Vec2(mtp(point.x), mtp(point.y)));
			Vec2 locate_point = this->getPosition();
			Vec2 draw_point = contact_point - locate_point;
			//	start -= locate_point;
			//	end -= locate_point;
			//	CCLOG("%f,%f,start", start.x, start.y);
			//	CCLOG("%f,%f,end", end.x, end.y);
			m_draw->drawCircle(draw_point, 1.0f, CC_DEGREES_TO_RADIANS(0), 50, false, Color4F(0, 1, 0, 1));
			//	auto s = String::createWithFormat("%d", i);
			//auto label = Label::createWithTTF(s->getCString(), "arial.ttf", 20);

			CCLOG("%f,%f,%d !!!area:%f!!BBBBBBB fail!!!!!!!!!", shapeBVertices[i].x, shapeBVertices[i].y, i, areaB);
		}
	}

#endif
	
	//clean  buffered  body and intersection point for the  next iterate
	this->removeTargetBodyAndPoint(body);
}

void  GameShatter::removeTargetBodyAndPoint(b2Body* body)
{
	std::map<b2Body*, b2Vec2>::iterator it_m = targetBody_map.find(body);
	if (it_m != targetBody_map.end())
	{
		targetBody_map.erase(it_m);
	}

	std::vector<b2Body*>::iterator it_v = std::find(targetBody_vector.begin(), targetBody_vector.end(), body);
	if (it_v != targetBody_vector.end())
	{
		targetBody_vector.erase(it_v);
	}


	std::vector<b2Body*>::iterator it_deleted = find(slicedBody_vector.begin(), slicedBody_vector.end(), body);
	{
		if (it_deleted == slicedBody_vector.end())
		{
			this->slicedBody_vector.push_back(body);
		}
	}



	std::vector<b2Body*>::iterator it_new = find(newBody_vector.begin(), newBody_vector.end(), body);
	{
		if (it_new != newBody_vector.end())
		{
			newBody_vector.erase(it_new);
		}
	}

}

bool GameShatter::createShatter(b2Body* origin_body, std::vector<b2Vec2> vertices)
{
	
	if (vertices.size() < 3 || vertices.size() > 8)
	{
		return false;
	}
	else
	{
		b2Fixture* origFixture = origin_body->GetFixtureList();
		b2BodyDef bodyDef;
		//bodyDef.type = b2_staticBody;
		bodyDef.type = b2_dynamicBody;
		b2Vec2  position;
		if (origin_body == this->m_targetBody)
		{
			position = m_targetLocation;
		}
		else
		{
			position = origin_body->GetPosition();
		}
		bodyDef.position = position;
		bodyDef.angle = origin_body->GetAngle();
		b2FixtureDef fixtureDef;
		fixtureDef.density = origFixture->GetDensity();
		fixtureDef.friction = origFixture->GetFriction();
		fixtureDef.restitution = origFixture->GetRestitution();
		fixtureDef.filter.groupIndex = 0;
		fixtureDef.filter.categoryBits = (uint16)collide_bit::SHATTER;
		fixtureDef.filter.maskBits = (uint16)collide_bit::PADDLE;
		//fixtureDef.filter.groupIndex = -1;
		//fixtureDef.filter.categoryBits = 0;
		//fixtureDef.filter.maskBits = 0;



		b2PolygonShape polyShape;
		b2Body* body = NULL;
		b2Vec2 *points = new b2Vec2[vertices.size()];

		float area = this->getArea(vertices);
		for (int i = 0; i < vertices.size(); i++)
		{
			points[i] = vertices[i];
		}
		polyShape.Set(points, vertices.size());
		fixtureDef.shape = &polyShape;

		body = m_world->CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		targetBody_vector.push_back(body);
		newBody_vector.push_back(body);

		return true;
	}


}

// function to get the area of a shape. I will remove tiny shape to increase performance
float GameShatter::getArea(std::vector<b2Vec2> vector)
{
	//设各顶点编号依次为1,2,3,...,n
	//	S = 1 / 2[(x1*y2 - x2*y1) + (x2*y3 - x3*y2) + ... + (xn - 1 * yn - xn*yn - 1) + (xn*y1 - x1*yn)]
	float area = 0.0f;
	int n = vector.size();
	for (int i = 0; i < n; i++)
	{
		b2Vec2 p1 = vector[i];
		b2Vec2 p2 = vector[i + 1<n ? i + 1 : 0];
		float e1X = p1.x * p2.y;
		float e1Y = p2.x * p1.y;
	
		float triangleArea = (e1X - e1Y);
		area += triangleArea;
	}
	area *= 0.5;
	return area;
}

float GameShatter::det(float x1, float y1, float x2, float y2, float x3, float y3)
{
	// This is a function which finds the determinant of a 3x3 matrix.  
	// If you studied matrices, you'd know that it returns 
	///1. a positive number if three given points are in clockwise order,
	///2. negative if they are in anti-clockwise order 
	///3. and zero if they lie on the same line.  
	// Another useful thing about determinants is that their absolute value is two times the face of the triangle, formed by the three given points.  
	return x1*y2 + x2*y3 + x3*y1 - y1*x2 - y2*x3 - y3*x1;
}


void  GameShatter::createNewBodyAndNewSprite()
{
	for (auto newBody : newBody_vector)
	{
		auto shatter = ShatterSprite::create(newBody, m_target);
		this->getParent()->addChild(shatter);
		this->shatter_vector.push_back(shatter);

	}

	//let the shatter fly away
	for (auto shatter : shatter_vector)
	{
		auto body = shatter->getB2Body();
		shatter->bomb(setExplosionVelocity(body));
		
	}
}

void  GameShatter::cleanOldBodyAndSprite()
{
	std::vector<b2Body*> eraser;
	for (auto body:slicedBody_vector)
	{
		eraser.push_back(body);
	}

	for (auto body : eraser)
	{
		Sprite* sprite = (Sprite*)body->GetUserData();
		if (sprite)
			sprite->removeFromParentAndCleanup(true);
		body->SetUserData(nullptr);
	
		m_world->DestroyBody(body);	
		
	}
}

bool GameShatter::CheckSegmentLength(std::vector<b2Vec2> vector)
{
	int cnt = vector.size();
	for (int32 i = 0; i < cnt; ++i)
	{
		int32 i1 = i;
		int32 i2 = i + 1 < cnt ? i + 1 : 0;
		b2Vec2 edge = vector[i2] - vector[i1];
		if (edge.LengthSquared() < 0.5f * b2_linearSlop)
		{

			for (int32 i = 0; i < cnt; ++i)
			{
				CCLOG("CHECK FALSE %f,%f,vector[%d],,,", vector[i].x, vector[i].y,i);
			}

			return false;
		}
		//if (!pointInBody(vector[i]))
		//{
		//	printf("illeage data (%f,%f)\n", vector[i].x, vector[i].y);
		//	return false;
		//}

		//for (int32 j = 0; j < cnt; ++j)
		//{
		//	// Don't check vertices on the current edge.  
		//	if (j == i1 || j == i2)
		//	{
		//		continue;
		//	}

		//	b2Vec2 r = vector[j] - vector[i1];

		//	// If this crashes, your polygon is non-convex, has colinear edges,  
		//	// or the winding order is wrong.  
		//	float32 s = sb2Cross(edge, r);
		//	if (s<0)
		//	{
		//		return false;
		//	}
		//}
	}
	return true;
}

bool GameShatter::pointInBody(const b2Vec2& point)
{
	return (point.x <= m_right && point.x >= m_left && point.y <= m_up && point.y >= m_bottom);
}

//若点a大于点b,即点a在点b顺时针方向,返回true,否则返回false
bool GameShatter::PointCompare(const b2Vec2 &a, const b2Vec2 &b, const b2Vec2 &center)
{
	if (a.x - center.x >= 0 && b.x - center.x < 0)
		return false;
	if (a.x - center.x < 0 && b.x - center.x >= 0)
		return true;
	if (a.x - center.x == 0 && b.x - center.x == 0) 
	{
		if (a.y - center.y >= 0 || b.y - center.y >= 0)
			return a.y < b.y;
		
		else
			return b.y < a.y;
	}
	//向量OA和向量OB的叉积
	float det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
	if (det == 0)
	{
		//向量OA和向量OB共线，以距离判断大小
		float d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
		float d2 = (b.x - center.x) * (b.x - center.y) + (b.y - center.y) * (b.y - center.y);
		return d1 < d2;
	}
	if (det < 0)
		return false;
	if (det > 0)
		return true;
	

	return false;
}

void GameShatter::ClockwiseSortPoints(std::vector<b2Vec2> &vector)
{
	//计算重心
	b2Vec2 center;
	float x = 0, y = 0;
	for (int i = 0; i < vector.size(); i++)
	{
		x += vector[i].x;
		y += vector[i].y;
	}
	center.x = x / vector.size();
	center.y = y / vector.size();

	//冒泡排序 可优化
	for (int i = 0; i < vector.size() - 1; i++)
	{
		for (int j = 0; j < vector.size() - i - 1; j++)
		{
			if (!PointCompare(vector[j], vector[j + 1], center))
			{
				b2Vec2 tmp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = tmp;
			}
		}
	}

}


b2Vec2 GameShatter::setExplosionVelocity(b2Body* body)
{
	float distX = body->GetWorldCenter().x - m_exploPoint.x;
	if (distX<0) {
		if (distX<-m_explosionRadius) 
		{
			distX = 0;
		}
		else 
		{
			distX = -m_explosionRadius - distX;
		}
	}
	else 
	{
		if (distX>m_explosionRadius)
		{
			distX = 0;
		}
		else 
		{
			distX = m_explosionRadius - distX;
		}
	}
	float distY = body->GetWorldCenter().y - m_exploPoint.y;
	if (distY<0) 
	{
		if (distY<-m_explosionRadius)
		{
			distY = 0;
		}
		else 
		{
			distY = -m_explosionRadius - distY;
		}
	}
	else 
	{
		if (distY>m_explosionRadius)
		{
			distY = 0;
		}
		else 
		{
			distY = m_explosionRadius - distY;
		}
	}
	distX *= 0.1;
	distY *= 0.1;
	return b2Vec2(distX, distY);
}