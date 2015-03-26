#ifndef BREAK_OUT_SHATTER_SPRITE
#define BREAK_OUT_SHATTER_SPRITE

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

struct V3F_C4B_T2F_POLY
{
	//! top left
	V3F_C4B_T2F  *vertice;
	GLuint        count;  //poly count

};

class ShatterSprite :public Sprite
{

public:
	static ShatterSprite* create(V3F_C4B_T2F_POLY poly,std::string file);
	ShatterSprite(V3F_C4B_T2F_POLY poly);
	~ShatterSprite();
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
	bool init(std::string file);
private:
	V3F_C4B_T2F_POLY poly_data;
	CustomCommand    command;
	void onDraw();


};









#endif