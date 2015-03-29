#ifndef BREAK_OUT_SHATTER_SPRITE
#define BREAK_OUT_SHATTER_SPRITE

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "PhysicsProtocol.h"
//#include <iostream>

USING_NS_CC;


class ShatterSprite :public Sprite, public PhysicsProtocol
{

public:
	static ShatterSprite* create(std::vector<b2Vec2>, Sprite*);
	ShatterSprite(std::vector<b2Vec2>, Sprite*);
	~ShatterSprite();
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
	bool init(Sprite*);
private:
	std::vector<b2Vec2> poly_data;
	int                 poly_count;
	V2F_C4F_T2F        *vertices;
	CustomCommand       command;
	Sprite             *originSprite;
	void onDraw();

	void setVerticesAndCoords();
};









#endif