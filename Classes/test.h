#pragma once

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"

#define PTM_RATIO 32.0

USING_NS_CC;

class test :public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(test);
	bool init() override;
	void update(float dt);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	~test();
private:
	void initPhysics();
	b2World       *_world;
	GLESDebugDraw *debugDraw;
	b2Body        *_body;
	Sprite        *_ball;
};