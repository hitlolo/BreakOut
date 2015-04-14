#ifndef BREAK_OUT_SHATTER_SPRITE
#define BREAK_OUT_SHATTER_SPRITE

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "PhysicsSprite.h"
#include "PhysicsProtocol.h"
//#include <iostream>

USING_NS_CC;


class ShatterSprite :public PhysicsSprite, public PhysicsProtocol
{

public:
	static ShatterSprite* create(b2Body* body, Sprite* originSprite);
	ShatterSprite(b2Body* body, Sprite* originSprite);
	~ShatterSprite();
	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	bool init(b2Body* body, Sprite* originSprite);
private:
	int                 poly_count;
	V2F_C4F_T2F        *vertices;
	CustomCommand       command;
	Sprite             *originSprite;
	Rect                textureRect;
	//bool                textureRect_Rotated;
	void onDraw();

	void initTextureRect(Sprite* originSprite);
	void setVerticesAndCoords(b2Body* body);

public:
	void bomb(b2Vec2 velocity);
};









#endif